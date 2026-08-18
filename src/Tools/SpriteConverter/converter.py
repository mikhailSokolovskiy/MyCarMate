from pathlib import Path
import re

from PIL import Image


SPRITE_WIDTH = 128
SPRITE_HEIGHT = 128

SUPPORTED_EXTENSIONS = {
    ".png",
    ".jpg",
    ".jpeg",
    ".bmp",
    ".webp",
}


def is_foreground(pixel, background):
    r, g, b, a = pixel
    br, bg, bb, _ = background

    if a < 128:
        return False

    distance = (
        (r - br) ** 2 +
        (g - bg) ** 2 +
        (b - bb) ** 2
    )

    return distance > 30 ** 2


def convert_image(input_path: Path, output_path: Path) -> None:
    if SPRITE_WIDTH <= 0 or SPRITE_HEIGHT <= 0:
        raise ValueError("Sprite dimensions must be positive.")

    if SPRITE_WIDTH % 8 != 0:
        raise ValueError(
            f"Sprite width must be divisible by 8. "
            f"Current width: {SPRITE_WIDTH}"
        )

    image = Image.open(input_path).convert("RGBA")

    image = image.resize(
        (SPRITE_WIDTH, SPRITE_HEIGHT),
        Image.Resampling.LANCZOS
    )

    pixels = image.load()

    # Верхний левый пиксель считаем цветом фона.
    background = pixels[0, 0]

    bytes_per_row = SPRITE_WIDTH // 8
    data: list[int] = []

    for y in range(SPRITE_HEIGHT):
        for byte_index in range(bytes_per_row):
            value = 0

            for bit in range(8):
                x = byte_index * 8 + bit
                pixel = pixels[x, y]

                if is_foreground(pixel, background):
                    value |= 1 << (7 - bit)

            data.append(value)

    write_header(output_path, data)


def write_header(output_path: Path, data: list[int]) -> None:
    variable_name = output_path.stem
    bytes_per_row = SPRITE_WIDTH // 8

    lines = []

    for i in range(0, len(data), bytes_per_row):
        row = data[i:i + bytes_per_row]

        values = ", ".join(
            f"0x{value:02X}"
            for value in row
        )

        lines.append(f"    {values},")

    output = (
        "#pragma once\n\n"
        "#include <cstdint>\n\n"
        f"constexpr uint8_t {variable_name}[] =\n"
        "{\n"
        + "\n".join(lines)
        + "\n"
        "};\n"
    )

    output_path.write_text(
        output,
        encoding="utf-8"
    )


def get_image_files(folder: Path) -> list[Path]:
    return sorted(
        [
            path
            for path in folder.iterdir()
            if path.is_file()
            and path.suffix.lower() in SUPPORTED_EXTENSIONS
        ],
        key=lambda path: path.name.lower()
    )


def create_sprite_block(name: str, frame_count: int) -> str:
    includes = "\n".join(
        f'#include "{name}/{name}_{i}.h"'
        for i in range(frame_count)
    )

    frames = ",\n".join(
        f"        {name}_{i}"
        for i in range(frame_count)
    )

    return (
        f"{includes}\n\n"
        f"namespace Sprites\n"
        f"{{\n"
        f"    constexpr const uint8_t* {name}[] =\n"
        f"    {{\n"
        f"{frames}\n"
        f"    }};\n\n"
        f"    constexpr size_t {name}Count = "
        f"sizeof({name}) / sizeof({name}[0]);\n"
        f"}}"
    )


def update_sprite_h(sprite_h_path: Path, name: str, frame_count: int) -> None:
    if not sprite_h_path.exists():
        raise FileNotFoundError(
            f"Не найден Sprite.h: {sprite_h_path}"
        )

    content = sprite_h_path.read_text(encoding="utf-8")

    # Ищем namespace Sprites целиком.
    namespace_pattern = re.compile(
        r"namespace\s+Sprites\s*\{.*?\n\}",
        re.DOTALL
    )

    namespace_match = namespace_pattern.search(content)

    if not namespace_match:
        raise ValueError(
            "В Sprite.h не найден namespace Sprites."
        )

    namespace_content = namespace_match.group(0)

    # Блок конкретного набора внутри namespace.
    block_pattern = re.compile(
        rf"\s*constexpr\s+const\s+uint8_t\*\s+"
        rf"{re.escape(name)}\[\]\s*="
        rf".*?"
        rf"constexpr\s+size_t\s+"
        rf"{re.escape(name)}Count\s*="
        rf".*?;",
        re.DOTALL
    )

    block_match = block_pattern.search(namespace_content)

    # Удаляем старый массив, если он уже существует.
    if block_match:
        old_block = block_match.group(0)

        namespace_content = (
            namespace_content[:block_match.start()]
            + namespace_content[block_match.end():]
        )

        # Убираем лишние пустые строки после удаления.
        namespace_content = re.sub(
            r"\n{3,}",
            "\n\n",
            namespace_content
        )

    # Удаляем старые include'ы этой эмоции.
    include_pattern = re.compile(
        rf'^\s*#include\s+"{re.escape(name)}/'
        rf'{re.escape(name)}_\d+\.h"\s*\n?',
        re.MULTILINE
    )

    content_without_includes = include_pattern.sub(
        "",
        content
    )

    # После удаления include'ов заново ищем namespace.
    namespace_match = namespace_pattern.search(
        content_without_includes
    )

    if not namespace_match:
        raise ValueError(
            "Не удалось найти namespace Sprites после обновления."
        )

    namespace_content = namespace_match.group(0)

    # Добавляем новый блок перед закрывающей } namespace.
    new_block = create_sprite_block(
        name,
        frame_count
    )

    namespace_open_end = namespace_content.rfind("}")

    namespace_content = (
        namespace_content[:namespace_open_end].rstrip()
        + "\n\n"
        + "\n".join(
            "    " + line
            for line in new_block.splitlines()
            if not line.startswith("namespace Sprites")
            and line != "}"
        )
        + "\n}"
    )

    # Добавляем include'ы сразу после существующих include'ов.
    includes = "\n".join(
        f'#include "{name}/{name}_{i}.h"'
        for i in range(frame_count)
    )

    include_position = namespace_match.start()

    updated_content = (
        content_without_includes[:include_position]
        + includes
        + "\n\n"
        + namespace_content
        + content_without_includes[
            namespace_match.end():
        ]
    )

    sprite_h_path.write_text(
        updated_content,
        encoding="utf-8"
    )


def main() -> int:
    script_folder = Path(__file__).resolve().parent

    # C:/.../Assets/Sprites
    sprites_folder = (
        script_folder.parent.parent
        / "Assets"
        / "Sprites"
    )

    sprite_h_path = sprites_folder / "SpriteList.h"

    image_files = get_image_files(script_folder)

    if not image_files:
        print("В папке конвертера не найдено изображений.")
        return 1

    print("=== Sprite Converter ===")
    print()
    print(f"Папка с изображениями: {script_folder}")
    print(f"Папка спрайтов:        {sprites_folder}")
    print(f"Sprite.h:              {sprite_h_path}")
    print(f"Найдено изображений:   {len(image_files)}")
    print()

    base_name = input(
        "Название набора (например Happy): "
    ).strip()

    if not base_name:
        print("Ошибка: название не может быть пустым.")
        return 1

    # Проверяем допустимость имени.
    if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", base_name):
        print(
            "Ошибка: название должно содержать только "
            "латинские буквы, цифры и _."
        )
        return 1

    # Assets/Sprites/<Emotion>
    output_folder = sprites_folder / base_name

    output_folder.mkdir(
        parents=True,
        exist_ok=True
    )

    print()
    print(f"Выходная папка: {output_folder}")
    print()

    for index, input_path in enumerate(image_files):
        output_name = f"{base_name}_{index}.h"
        output_path = output_folder / output_name

        print(
            f"[{index + 1}/{len(image_files)}] "
            f"{input_path.name} -> "
            f"{base_name}/{output_name}"
        )

        try:
            convert_image(
                input_path,
                output_path
            )
        except Exception as exc:
            print(
                f"Ошибка при обработке "
                f"{input_path.name}: {exc}"
            )
            return 1

    try:
        update_sprite_h(
            sprite_h_path,
            base_name,
            len(image_files)
        )
    except Exception as exc:
        print(f"\nОшибка при обновлении Sprite.h: {exc}")
        return 1

    print()
    print("================================")
    print("Готово!")
    print()
    print(f"Создано кадров: {len(image_files)}")
    print(f"Папка: {output_folder}")
    print(f"Обновлён: {sprite_h_path}")
    print(
        f"Размер спрайта: "
        f"{SPRITE_WIDTH}x{SPRITE_HEIGHT}"
    )
    print(
        f"Размер данных одного спрайта: "
        f"{SPRITE_WIDTH * SPRITE_HEIGHT // 8} байт"
    )
    print("================================")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())