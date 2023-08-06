absolute :: Int -> Int
-- absolute n = if n >= 0 then n else -n
absolute n
  | n >= 0 = n
  | otherwise = -n

signalNumber :: Int -> Int
-- signalNumber n = if n < 0 then -1 else
--                      if n == 0 then 0 else 1
signalNumber n
  | n < 0 = -1
  | n == 0 = 0
  | otherwise = 1

