#!/bin/bash

# Requirement 1: Check whether exactly 3 arguments are given
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <src_dir> <backup_dir> <extension>"
    exit 1
fi

SRC="$1"
DEST="$2"
EXT="$3"

# Check if the source directory exists, if not, create it
if [ ! -d "$SRC" ]; then
    echo "$SRC does not exist."
    echo "Creating source directory: $SRC"
    mkdir -p "$SRC"
fi

# Requirement 2: Use globbing to find files with the given extension in SRC

shopt -s nullglob  #  prevent expand to  src/*.ext when no  file present"
ip_files=($SRC/*$EXT)
shopt -u nullglob

# exporting backup cnt
export BACKUP_COUNT=0

# check and create backup dir
if [ ! -d "$DEST" ]; then
    mkdir -p "$DEST"
    if [ $? -ne 0 ]; then
        echo "$DEST creation failed"
        exit 1
    fi
fi

total_size=0 

# Check if any matching files exist
if [[ ${#ip_files[@]} -eq 0 ]]; then
    echo "No files exist with the extension $EXT in $SRC"
else
    echo "Found files:"
    for file in "${ip_files[@]}"; do
	size=$(stat -c%s "$file")
	echo "$file - $size byets" 

	dest_file="$DEST/$(basename "$file")"
    	if [ -f "$dest_file" ]; then
             if [ "$file" -nt "$dest_file" ]; then
            	cp "$file" "$DEST"
            	echo "$dest_file is older so over wite it"
            	BACKUP_COUNT=$((BACKUP_COUNT +1))
		total_size=$((total_size + size))
             else
            	echo "skip $file  as  $dest_file is latest version"
	     fi

	else
		echo "cpy $file to $DEST"
		cp "$file" "$DEST"
	    	BACKUP_COUNT=$((BACKUP_COUNT + 1))
		total_size=$((total_size + size))
    fi
    done
fi


report="$DEST/backup_report.log"

{
    echo "Backup Summary Report"
    echo "----------------------"
    echo "Src: $SRC"
    echo "DEST: $DEST"
    echo "EXT: $EXT"
    echo "Total Files: ${#ip_files[@]}"
    echo "Total Files Backup: ${BACKUP_COUNT}"
    echo "Total Backup Size: ${total_size} bytes"
    echo "Backup done on : $(date)"
} > "$report" && cat "$report"

export BACKUP_COUNT
