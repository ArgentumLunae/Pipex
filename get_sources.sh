rm sources.mk
echo "SRC		:= " | tr -d '\n' >> sources.mk
ls src/ | sed -e s/$/' \\'/  >> sources.mk