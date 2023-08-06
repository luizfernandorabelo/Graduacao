buildPairSequence :: [String] -> [String]

buildPairSequence [] = []

buildPairSequence (x1':x2':xs)
  | (x1 == 10) && (length xs == 1)      = [buildTrioFromStrike x2' (head xs)]
  | x1 == 10                            = "X _" : buildPairSequence (x2':xs)
  | (x1 + x2 == 10) && (length xs == 1) = [buildTrioFromSpare x1' (head xs)]
  | x1 + x2 == 10                       = (x1' ++ " /") : buildPairSequence xs
  | otherwise                           = (x1' ++ " " ++ x2') : buildPairSequence xs
  where
    x1 = read x1' :: Int
    x2 = read x2' :: Int


---
buildTrioFromStrike :: String -> String -> String

buildTrioFromStrike x2' x3'
  | (x2 == 10) && (x3 == 10) = "X X X"
  | x2 + x3 == 10            = "X " ++ x2' ++ " /"
  | otherwise                = "X " ++ x2' ++ " " ++ x3'
  where
    x2 = read x2' :: Int
    x3 = read x3' :: Int


---
buildTrioFromSpare :: String -> String -> String

buildTrioFromSpare x1' x3'
  | x3 == 10  = x1' ++ " / X"
  | otherwise = x1' ++ " / " ++ x3'
  where
    x3 = read x3' :: Int


---
printPairSequence :: [String] -> IO ()

printPairSequence [] = do putStr ""

printPairSequence (p:ps) = do
  putStr (p ++ " | ")
  printPairSequence ps


---
buildPlayBonuses :: [(Int,String)] -> [Int]

buildPlayBonuses = foldr
      (\ p
         -> (++)
              ([if (x == 'X') && (n < 10) then
                    2
                else
                    if (x == '/') && (n < 10) then 1 else 0 |
                  let n = fst p,
                  let ws = snd p,
                  xs <- words ws,
                  x <- xs,
                  x /= ' ',
                  x /= '_']))
      []


---
evaluateScore :: [String] -> [Int] -> Int

evaluateScore [p1', p2'] _ = p1 + p2
  where
    p1 = read p1' :: Int
    p2 = read p2' :: Int

evaluateScore (p1':p2':p3':ps) (b1:b2:b3:bs) = p1 + s + evaluateScore (p2':p3':ps) (b2:b3:bs)
  where
    p1 = read p1' :: Int
    p2 = read p2' :: Int
    p3 = read p3' :: Int
    s | b1 == 2   = p2 + p3
      | b1 == 1   = p2
      | otherwise = 0


---
main :: IO ()
main = do
  plays <- getLine
  let pairSequence = buildPairSequence (words plays)
  let bonuses = buildPlayBonuses (zip [1..] pairSequence)
  let score = evaluateScore (words plays) bonuses
  printPairSequence pairSequence
  print score
