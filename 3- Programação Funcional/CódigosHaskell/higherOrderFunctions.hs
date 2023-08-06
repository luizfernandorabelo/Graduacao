-- built-in functions:
-- map :: (a -> b) -> [a] -> [b]
--    map (+1) [0,1,2,3,4,5]  -- [1,2,3,4,5,6]
-- filter :: (a -> Bool) -> [a] -> [a]
--    filter even [1..10]  -- [2,4,6,8,10]

myMap1 :: (a -> b) -> [a] -> [b]
myMap1 _ [] = []
myMap1 f (x:xs) = f x : myMap1 f xs

myMap2 :: (t -> a) -> [t] -> [a]
myMap2 f xs = [f x | x <- xs]

myFilter1 :: (a -> Bool) -> [a] -> [a]
myFilter1 _ [] = []
myFilter1 f (x:xs) = if f x then x : myFilter1 f xs else myFilter1 f xs

myFilter2 :: (a -> Bool) -> [a] -> [a]
myFilter2 f xs = [x | x <- xs, f x]
