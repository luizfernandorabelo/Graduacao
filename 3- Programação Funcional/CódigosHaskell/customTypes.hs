type Pos = (Int,Int)

origin :: Pos
origin = (0,0)


data Answer = Yes | No | Unknown

answers :: [Answer]
answers = [Yes, No, Unknown]


data Shape = Circle Float | Rect Float Float

square :: Float -> Shape
square n = Rect n n

area :: Shape -> Float
area (Circle r) = pi * r^2
area (Rect x y) = x * y
