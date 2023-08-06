act :: IO (Char,Char)
act = do  x <- getChar
          y <- getChar
          return (x,y)

-- how getline is implemented:
-- getLine :: IO String
-- getLine = do  x <- getChar
--               if x == '\n' then
--                 return []
--               else 
--                 do  xs <- getLine
--                     return (x:xs)

strlen :: IO ()
strlen = do putStr "Enter a string: "
            xs <- getLine
            putStr "The string has "
            putStr (show (length xs))  -- show converts the length to a string to be displayed
            putStrLn " characters"
