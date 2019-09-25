import System.IO
import Control.Monad

import System.Process
test = readProcess "/usr/bin/git" ["log", "--author=jkaba", "--reverse"] []
main :: IO ()
main = test >>= putStrLn

