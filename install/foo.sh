free -m | awk 'NR==2{ printf("%4.1f /%4.1f GB", $3/1024, $2/1024) }'

