insert :: Ord a => a -> [a] -> [a]
insert n' [] = [n']
insert n' (n:ns)
  | n' < n = n' : n : ns
  | otherwise = n : insert n' ns

insertionSort :: Ord a => [a] -> [a]
insertionSort [] = []
insertionSort (n:ns) = insert n (insertionSort ns)

quickSort :: Ord a => [a] -> [a]
quickSort [] = []
quickSort (n:ns) = quickSort smaller ++ [n] ++ quickSort larger
    where
        smaller = [n' | n' <- ns, n' <= n]
        larger = [n' | n' <- ns, n' > n]

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
  | x <= y = x : merge xs (y:ys)
  | otherwise = y : merge (x:xs) ys

halve :: [a] -> ([a],[a])
halve xs = (h1, h2)
  where
    h1 = [x | (x,i) <- zip xs [0..], i < length xs `div` 2]
    h2 = [x | (x,i) <- zip xs [0..], i >= length xs `div` 2]

mergeSort :: Ord a => [a] -> [a]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort xs = merge (mergeSort ys) (mergeSort zs) where (ys,zs) = halve xs
