###CMPE 460 HW 1
####Input
Program expects an argument for input file. First line of input file must contain an integer and match the number of surfaces defined in input file. Surfaces can be defined as
```x y z r g b radius``` where all the variables are type of c++ float, and ```r g b``` values must be less than ```COLOR_MAX``` value. Example input file:

```text
2
20 40 50 255 255 230 40
42.5 40.32 50.4 242.2 255.3 230.2 40.1
```

Program should be called like ```./ray.exe input```