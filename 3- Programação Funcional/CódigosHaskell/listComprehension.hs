-- the [startN..endN] is called GENERATOR.

-- [x^2 | x <- [0..5]]  -- [0,1,4,9,16,25]
-- [(x,y) | x <- [1,2,3], y <- [4,5]]  -- [(1,4),(1,5),(2,4),(2,5),(3,4),(3,5)]
-- [(x,y) | x <- [1..3], y <- [x..3]]  -- [(1,1),(1,2),(1,3),(2,1),(2,2),(2,3),(3,3)]

concatenate :: [[a]] -> [a]
concatenate nss = [n | ns <- nss, n <- ns]

-- [x | x <- [1..10], even x]  -- [2,4,6,8,10]

factors :: Int -> [Int]
factors n = [d | d <- [1..n], n `mod` d == 0]

prime :: Int -> Bool
prime n = factors n == [1, n]

-- returns all the prime numbers up to l
primes :: Int -> [Int]
primes l = [n | n <- [1..l], prime n]

positions :: Eq a => a -> [a] -> [Int]
positions x xs = [i | (i, x') <- zip [0..] xs, x' == x]

count :: Char -> String -> Int
count c cs = length [c' | c' <- cs, c' == c]
