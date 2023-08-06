factors :: Int -> [Int]
factors n = [d | d <- [1..n], n `mod` d == 0]

perfects :: Int -> [Int]
perfects n = [n' | n' <- [1..n], sum (init (factors n')) == n']
