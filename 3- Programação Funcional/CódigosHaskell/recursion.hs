myAnd :: [Bool] -> Bool
myAnd [] = True
myAnd (x:xs) = x && myAnd xs

concatenate :: [[a]] -> [a]
concatenate [] = []
concatenate (xs:xss) = xs ++ concatenate xss

produceList :: Int -> a -> [a]
produceList 0 v = []
produceList n v = v : produceList (n-1) v

selectNth :: [a] -> Int -> a
selectNth [] _ = error "Index out of bounds!"
selectNth (x:_) 0 = x
selectNth (_:xs) n = selectNth xs (n-1)

isElement :: Eq a => a -> [a] -> Bool
isElement _ [] = False
isElement x (x':xs) = x' == x || isElement x xs
