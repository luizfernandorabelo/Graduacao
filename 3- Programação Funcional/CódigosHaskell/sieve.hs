primes :: [Integer]
primes = sieve [2..]

sieve :: Integral a => [a] -> [a]
sieve (p:xs) = p : sieve [x | x <- xs, x `mod` p /= 0]

twin :: (Eq a, Num a) => (a, a) -> Bool
twin (x,y) = y == x+2

twins :: [(Integer, Integer)]
twins = filter twin (zip primes (tail primes))
