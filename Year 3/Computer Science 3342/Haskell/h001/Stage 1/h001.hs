import System.Process
test = readProcess "/usr/bin/git" ["log"] []
main :: IO ()
main = test >>= putStrLn
