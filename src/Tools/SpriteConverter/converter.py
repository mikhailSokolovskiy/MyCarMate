from pathlib import Path
import sys

from PIL import Image


# ============================================================
# Configuration
# ============================================================

SPRITE_WIDTH = 128
SPRITE_HEIGHT = 128

# Pixels brighter than this value become 1.
# Pixels below this value become 0.
THRESHOLD = 128

# Input:
#   light pixel  -> 1
#   dark pixel   -> 0
#
# If the source image has transparency:
#   transparent -> 0


# ============================================================
# Conversion
# ============================================================

def convert_image(input_path: Path, output_path: Path) -> None:
    if SPRITE_WIDTH <= 0 or SPRITE_HEIGHT <= 0:
        raise ValueError("Sprite dimensions must be positive.")

    if SPRITE_WIDTH % 8 != 0:
        raise ValueError(
            f"Sprite width must be divisible by 8. "
            f"Current width: {SPRITE_WIDTH}"
        )

    if not input_path.exists():
        raise FileNotFoundError(
            f"Input image not found: {input_path}"
        )

    image = Image.open(input_path).convert("RGBA")

    image = image.resize(
        (SPRITE_WIDTH, SPRITE_HEIGHT),
        Image.Resampling.LANCZOS
    )

    pixels = image.load()
    bytes_per_row = SPRITE_WIDTH // 8

    data: list[int] = []

    for y in range(SPRITE_HEIGHT):
        for byte_index in range(bytes_per_row):
            value = 0

            for bit in range(8):
                x = byte_index * 8 + bit

                r, g, b, a = pixels[x, y]

                if a >= 128:
                    value |= 1 << (7 - bit)

            data.append(value)

    write_header(output_path, data)


# ============================================================
# Header generation
# ============================================================

def write_header(output_path: Path, data: list[int]) -> None:
    variable_name = output_path.stem

    lines: list[str] = []

    for i in range(0, len(data), SPRITE_WIDTH // 8):
        row = data[i:i + SPRITE_WIDTH // 8]

        values = ", ".join(
            f"0x{value:02X}"
            for value in row
        )

        lines.append(f"    {values},")

    output = (
        "#pragma once\n"
        "\n"
        "#include <cstdint>\n"
        "\n"
        f"constexpr uint8_t {variable_name}[] =\n"
        "{\n"
        + "\n".join(lines)
        + "\n"
        "};\n"
    )

    output_path.parent.mkdir(
        parents=True,
        exist_ok=True
    )

    output_path.write_text(
        output,
        encoding="utf-8"
    )


# ============================================================
# Main
# ============================================================

def main() -> int:
    if len(sys.argv) != 3:
        print(
            "Usage:\n"
            "  python converter.py <input> <output.h>\n\n"
            "Example:\n"
            "  python converter.py Happy_0.png Happy_0.h"
        )

        return 1

    input_path = Path(sys.argv[1])
    output_path = Path(sys.argv[2])

    try:
        convert_image(
            input_path,
            output_path
        )

        data_size = (
            SPRITE_WIDTH *
            SPRITE_HEIGHT //
            8
        )

        print("Conversion complete.")
        print(f"Input : {input_path}")
        print(f"Output: {output_path}")
        print(
            f"Size  : "
            f"{SPRITE_WIDTH}x{SPRITE_HEIGHT}"
        )
        print(
            f"Data  : "
            f"{data_size} bytes"
        )

        return 0

    except Exception as exc:
        print(f"Error: {exc}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())