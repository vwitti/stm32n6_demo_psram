#!/bin/bash
## Helper functions used in several scripts ###

### set a key-value pair in a file ###
set_key_value_pair() {
    local file="$1"
    local key="$2"
    local val="$3"

    if grep -q "^${key}=" "$file"; then
        # Key existiert --> ersetzen
        sed -i "s|^${key}=.*|${key}=${val}|" "$file"
    else
        # Key existiert nicht --> anhängen
        echo "${key}=${val}" >> "$file"
    fi
}
