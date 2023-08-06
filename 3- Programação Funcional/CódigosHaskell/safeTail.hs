safetailA :: [a] -> [a]
safetailA ns = if not (null ns) then tail ns else []

safetailB :: [a] -> [a]
safetailB ns
  | not (null ns) = tail ns
  | otherwise = []

safetailC :: [a] -> [a]
safetailC [] = []
safetailC (_:xs) = xs
