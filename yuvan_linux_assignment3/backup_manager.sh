
#!/bin/bash
{
#Problem1
if [[ $# -ne 3 ]]; then
  echo "Require exactly 3 arguments"
  exit 1
fi

src="$1"
backup="$2"
ext="$3"
#Problem 2&4
backup_files=("$src"/*"$ext")

if [[ ${#backup_files[@]} -eq 0 ]]; then
    echo "No such files in extension $ext"
    exit 1
fi

for file in "${backup_files[@]}"; do
    size=$(stat -c%s "$file")
    echo "$file, size=$size"
done

#Problem 3
export BACKUP_COUNT=0

#Problem 5
if [[ ! -d "$backup" ]]; then
  mkdir -p "$backup"
fi

backup_size=0

echo "Backup in Process"

for file in "${backup_files[@]}"; do
  DEST_FILE="$backup/$(basename "$file")"
  if [[ ! -e "$DEST_FILE" || "$file" -nt "$DEST_FILE" ]]; then
    cp "$file" "$DEST_FILE"
    ((BACKUP_COUNT++))
    ((backup_size += $(stat -c%s "$file")))
  else
    echo "$file is up to date, SKIPPED"
  fi
done

{
  echo "Total Files Processed: $BACKUP_COUNT"
  echo "Total Size of Files Backed Up: $backup_size bytes"
  echo "Backup Directory: $backup"
} > "$backup/backup_report.log"

echo "Backup Succesful"
} > output.txt