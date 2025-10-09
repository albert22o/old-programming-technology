#!/usr/bin/env bash
# gen_dot_pngs.sh
# Генерирует .png из всех .dot в папках diagrams и correct_diagrams
# Usage:
#   ./gen_dot_pngs.sh                # ищет в ./diagrams и ./correct_diagrams
#   ./gen_dot_pngs.sh /path/to/project
#   ./gen_dot_pngs.sh /path/to/project --verbose

set -u

# Параметры
BASE_DIR="${1:-.}"       # первый аргумент — корневая папка проекта (по умолчанию текущая)
VERBOSE=0
if [[ "${2:-}" == "--verbose" || "${1:-}" == "--verbose" ]]; then
  VERBOSE=1
fi

# если передали только --verbose как первый аргумент
if [[ "$BASE_DIR" == "--verbose" ]]; then
  BASE_DIR="."
  VERBOSE=1
fi

DOT_CMD="$(command -v dot || true)"
if [[ -z "$DOT_CMD" ]]; then
  echo "Ошибка: утилита 'dot' (Graphviz) не найдена в PATH."
  echo "Установите graphviz (например: sudo apt install graphviz) и повторите."
  exit 2
fi

# именованные папки для обхода
DIRS=( "diagrams" "correct_diagrams" )

# собрать все .dot файлы (null-terminated), обработать по одному
FOUND=0
while IFS= read -r -d '' dotfile; do
  FOUND=1
  pngfile="${dotfile%.dot}.png"

  if [[ $VERBOSE -eq 1 ]]; then
    echo "Processing: '$dotfile' -> '$pngfile'"
  fi

  # создать папку вывода на случай, если .dot в поддиректории (обычно не нужно)
  outdir="$(dirname "$pngfile")"
  if [[ ! -d "$outdir" ]]; then
    mkdir -p "$outdir"
  fi

  if ! "$DOT_CMD" -Tpng "$dotfile" -o "$pngfile"; then
    echo "Warning: не удалось сгенерировать PNG для '$dotfile'" >&2
  else
    if [[ $VERBOSE -eq 1 ]]; then
      echo "  -> OK"
    fi
  fi
done < <(find "$BASE_DIR" \( -path "$BASE_DIR/diagrams" -o -path "$BASE_DIR/correct_diagrams" -o -path "$BASE_DIR/diagrams/*" -o -path "$BASE_DIR/correct_diagrams/*" \) -type f -name "*.dot" -print0 2>/dev/null)

if [[ $FOUND -eq 0 ]]; then
  echo "Ничего не найдено: в '$BASE_DIR' нет .dot в папках diagrams или correct_diagrams."
  exit 1
fi

echo "Генерация завершена."
exit 0
