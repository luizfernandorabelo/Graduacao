import System.IO

hangman :: IO ()
hangman = do putStrLn "Think of a word:"
             word <- sGetLine
             putStrLn "Try to guess it:"
             play word

sGetLine :: IO String
sGetLine = do x <- sGetChar
              if x == '\n' then
                do putChar x
                   return []
              else
                do putChar '*'
                   xs <- sGetLine
                   return (x:xs)

sGetChar :: IO Char
sGetChar = do hSetEcho stdin False
              x <- getChar
              hSetEcho stdin True
              return x

play :: String -> IO ()
play word = do putStr "? "
               guess <- getLine
               if guess == word then
                 putStrLn "You got it!"
               else
                 do putStrLn (match word guess)
                    play word

match :: String -> String -> String
match ws gs = [if w `elem` gs then w else '-' | w <- ws]
