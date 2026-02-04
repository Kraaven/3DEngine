#!/bin/sh
# gen_ds.sh - Generate data structures from ds_types.txt

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEMPLATE_DIR="$SCRIPT_DIR/../data_structures/templates"
OUT_DIR="$SCRIPT_DIR/../data_structures/generated"
TYPE_FILE="$SCRIPT_DIR/ds_types.txt"

# --- Sanity checks ---
if [ ! -f "$TYPE_FILE" ]; then
  echo "Error: ds_types.txt not found"
  exit 1
fi

TEMPLATE_FILES=$(find "$TEMPLATE_DIR" -maxdepth 1 -type f -name "*.template.h")

if [ -z "$TEMPLATE_FILES" ]; then
  echo "Error: No templates found in $TEMPLATE_DIR"
  exit 1
fi

# --- Clean generated directory ---
echo "🧹 Cleaning generated directory..."
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

echo "📦 Generating data structures..."
echo ""

# --- Process each type ---
while IFS= read -r LINE || [ -n "$LINE" ]; do
  # Remove comments and trim
  LINE=$(echo "$LINE" | sed 's/#.*//' | xargs)
  [ -z "$LINE" ] && continue

  set -- $LINE

  TYPE_NAME=""
  FINAL_TYPE=""
  TYPE_INCLUDES=""

  if [ "$1" = "struct" ]; then
    STRUCT_NAME="$2"
    TYPE_NAME="$STRUCT_NAME"
    FINAL_TYPE="struct $STRUCT_NAME *"

    shift 2
    for inc in "$@"; do
      TYPE_INCLUDES="$TYPE_INCLUDES\n#include \"$inc\""
    done
  else
    TYPE_NAME="$1"
    FINAL_TYPE="$1"
  fi

  echo "→ $TYPE_NAME"

  for tpl in $TEMPLATE_FILES; do
    base=$(basename "$tpl" .template.h)
    out="$OUT_DIR/${base}_${TYPE_NAME}.h"

    sed \
      -e "s/{{TYPE_NAME}}/$TYPE_NAME/g" \
      -e "s/{{TYPE}}/$FINAL_TYPE/g" \
      -e "s|{{TYPE_INCLUDES}}|$TYPE_INCLUDES|g" \
      "$tpl" >"$out"

    echo "  ✔ $(basename "$out")"
  done

  echo ""
done <"$TYPE_FILE"

echo "✅ All data structures generated successfully in '$OUT_DIR'"
