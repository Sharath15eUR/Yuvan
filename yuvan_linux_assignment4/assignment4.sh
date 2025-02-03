if [[ $# -ne 1 ]]; then
    echo "Command line needs exactly one argument"
    exit 1
fi

INP="$1"
OUT="out.txt"

while IFS= read -r line; do
    FRAME_TIME=$(echo "$line" | grep -oP '(?<=frame.time": ")[^"]*')
    WLAN_TYPE=$(echo "$line" | grep -oP '(?<=wlan.fc.type": ")[^"]*')
    WLAN_SUBTYPE=$(echo "$line" | grep -oP '(?<=wlan.fc.subtype": ")[^"]*')

    if [[ -n "$FRAME_TIME" || -n "$WLAN_TYPE" || -n "$WLAN_SUBTYPE" ]]; then
        [[ -n "$FRAME_TIME" ]] && echo "frame time: $FRAME_TIME" >> "$OUT"
        [[ -n "$WLAN_TYPE" ]] && echo "wlan fc type: $WLAN_TYPE" >> "$OUT"
        [[ -n "$WLAN_SUBTYPE" ]] && echo "wlan fc subtype: $WLAN_SUBTYPE" >> "$OUT"
        echo >> "$OUT"
    fi
done < "$INP"
