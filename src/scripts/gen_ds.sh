#!/bin/sh
# gen_ds.sh - Generate all dynamic data structures for a given type
# Automatically finds all templates in data_structures/templates/

set -e # Exit on any error

# --- Check arguments ---
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <TYPE> <TYPE_NAME>"
  echo "Example: $0 int int"
  echo "         $0 'struct vec3' vec3"
  exit 1
fi

TYPE="$1"
TYPE_NAME="$2"

# --- Absolute paths ---
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEMPLATE_DIR="$SCRIPT_DIR/../data_structures/templates"
OUT_DIR="$SCRIPT_DIR/../data_structures/generated"

mkdir -p "$OUT_DIR"

# --- Debug info ---
echo "Generating data structures for type: $TYPE"
echo "Type name: $TYPE_NAME"
echo "Template dir: $TEMPLATE_DIR"
echo "Output dir: $OUT_DIR"
echo ""

# --- Find all templates ---
TEMPLATE_FILES=$(find "$TEMPLATE_DIR" -maxdepth 1 -type f -name "*.template.h")

if [ -z "$TEMPLATE_FILES" ]; then
  echo "Error: No templates found in $TEMPLATE_DIR"
  exit 1
fi

# --- Generate each template ---
for tpl_path in $TEMPLATE_FILES; do
  tpl_file=$(basename "$tpl_path") # e.g., stack.template.h
  base="${tpl_file%.template.h}"   # e.g., stack
  out_file="$OUT_DIR/${base}_${TYPE_NAME}.h"

  sed -e "s/{{TYPE}}/$TYPE/g" \
    -e "s/{{TYPE_NAME}}/$TYPE_NAME/g" \
    "$tpl_path" \
    >"$out_file"

  echo "Generated: $out_file"
done

echo ""
echo "✅ All data structures generated successfully in '$OUT_DIR'"
