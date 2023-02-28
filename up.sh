

note=$1


git add .
git commit -m "${note}"
git push

echo "end. "$(date)