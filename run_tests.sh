#!/bin/bash
find ./tests -name '*.k' -exec ./build/bin/main {} -o ./build/tests/{}.ll \;
#find ./tests -name '*.k' -exec ./build/bin/main {} \;
