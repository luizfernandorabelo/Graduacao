add :: (Int,Int) -> Int
add (x,y) = x + y

zeroTo :: Int -> [Int]
zeroTo n = [0..n]

add' :: Int -> Int -> Int
add' x y = x + y

multiply :: Int -> Int -> Int -> Int
multiply x y z = x * y * z

getSuccessor :: Int -> Int
getSuccessor = (+ 1)

odds :: Int -> [Int]
odds n = map f [0..n-1] where f x = x*2 + 1

evens :: Int -> [Int]
-- evens n = map (\x -> x*2) [0..n-1]
evens n = map (* 2) [0..n-1]
