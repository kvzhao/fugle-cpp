## OSX
find project/ -type f \( -name '*.c' -o -name '*.cpp' -o -name '*.hpp' \) -print0 | xargs -0 -I{} clang-format -i {}

## Linux
# find project/ -type f -name '*.c' -o -name '*.cpp' -o -name '*.hpp' | xargs -i clang-format -i {}