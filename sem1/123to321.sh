read -p "Write the path to the folder: " folder

if [ ! -d "$folder" ]; then
    echo "Folder doesn't exist."
    exit 1
fi

find "$folder" -type f | while read -r file; do
    if [ $(($(date +%s) - $(stat -c %Y "$file"))) -gt 120 ]; then
        temp_file="${file}.new"
        
        while IFS= read -r line; do
            echo "${line//123/321}"
        done < "$file" > "$temp_file"
        
        mv -f "$temp_file" "$file"
    else
        echo "Skipping $file (modified less than 2 minutes ago)"
    fi
done

echo "Completed."
