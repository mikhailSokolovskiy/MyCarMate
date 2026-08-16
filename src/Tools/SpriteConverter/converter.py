from pathlib import Path

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


def main() -> int:
    script_folder = Path(__file__).resolve().parent

    image_files = get_image_files(script_folder)

    if not image_files:
        print("В папке конвертера не найдено изображений.")
        return 1

    print("=== Sprite Converter ===")
    print()
    print(f"Папка: {script_folder}")
    print(f"Найдено изображений: {len(image_files)}")
    print()

    base_name = input(
        "Название набора (например Happy): "
    ).strip()

    if not base_name:
        print("Ошибка: название не может быть пустым.")
        return 1

    print()

    for index, input_path in enumerate(image_files):
        output_name = f"{base_name}_{index}.h"
        output_path = script_folder / output_name

        print(
            f"[{index + 1}/{len(image_files)}] "
            f"{input_path.name} -> {output_name}"
        )

        try:
            convert_image(
                input_path,
                output_path
            )
        except Exception as exc:
            print(f"Ошибка при обработке {input_path.name}: {exc}")
            return 1

    print()
    print("Готово.")
    print(f"Размер спрайта: {SPRITE_WIDTH}x{SPRITE_HEIGHT}")
    print(
        f"Размер данных одного спрайта: "
        f"{SPRITE_WIDTH * SPRITE_HEIGHT // 8} байт"
    )

    return 0


if __name__ == "__main__":
    raise SystemExit(main())