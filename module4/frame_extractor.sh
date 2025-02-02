#!/bin/bash

# Check if input is given
if [ $# -ne 2 ]; then
    echo " usage: frame_extractor.sh <in_file> <out_file>"
    exit 1
fi

in_file="$1"
out_file="$2"


# Initialize temporary variables to hold values
frame_time=""
wlan_fc_type=""
wlan_fc_subtype=""

# Fields to extract
fields=("frame.time" "wlan.fc.type" "wlan.fc.subtype")

# Read the input file line by line
while IFS= read -r line; do
    # Check if  curret line consist the desired field for the fields array
    for field in "${fields[@]}"; do
        if [[ "$line" == *"$field"\":* ]]; then
            value=$(echo "$line" | sed -E "s/.*\"$field\": \"(.*)\".*/\1/") #s/expr/ \1 / => /1 is the first grp  captured using(.*)
            # Store value in respective varialbe
            case "$field" in
                "frame.time")
                    frame_time="$value"
                    ;;
                "wlan.fc.type")
                    wlan_fc_type="$value"
                    ;;
                "wlan.fc.subtype")
                    wlan_fc_subtype="$value"
                    ;;
            esac
        fi
    done

    # Write  when all 3 params are extracted  as a single set of content
    if [[ -n "$frame_time" && -n "$wlan_fc_type" && -n "$wlan_fc_subtype" ]]; then
        echo "\"frame.time\": \"$frame_time\"" >> "$out_file"
        echo "\"wlan.fc.type\": \"$wlan_fc_type\"" >> "$out_file"
        echo "\"wlan.fc.subtype\": \"$wlan_fc_subtype\"" >> "$out_file"
        echo "" >> "$out_file"  
        frame_time=""
        wlan_fc_type=""
        wlan_fc_subtype=""
    fi

done < "$in_file"

echo "Extraction finished , refer $out_file for extraction resutls"
