import System.IO
import Control.Monad
import System.Process
import Data.String

-- Short code for stage 1-3
-- test = readProcess "/usr/bin/git" ["log", "--author=jkaba", "--reverse"] []
-- main :: IO ()
-- main = test >>= putStrLn

main = do
    let list = []
    handle <- openFile "test.txt" ReadMode
    contents <- hGetContents handle
    let singlewords = words contents
        list = singlewords

    -- UGLY CODE BLOCK
    -- DOING THIS THE LONG WAY
    -- HOPEFULLY WILL FIX LATER
    -- USING read from text and then reverse

    --let y = 0
    print "Input a type(0 for js, 1 for ruby, 2 for haskell): "
    y <- getLine

    case compare y "0" of
        LT -> do print " "
        GT -> do print " "

        EQ -> do
            print "Javascript Tasks"
            print " "

            let x = list!!8 ++ " " ++ list!!9 ++ " " ++ list!!10 ++ " " ++ list!!11 ++ " " ++ list!!1
            print x
            let x = list!!13 ++ " " ++ list!!14 ++ " " ++ list!!15 ++ " " ++ list!!16 ++ " " ++ list!!17
            print x
            let x = list!!19 ++ " " ++ list!!20 ++ " " ++ list!!21
            print x
            print " "


            let x = list!!30 ++ " " ++ list!!31 ++ " " ++ list!!32 ++ " " ++ list!!33 ++ " " ++ list!!23
            print x
            let x = list!!35 ++ " " ++ list!!36 ++ " " ++ list!!37 ++ " " ++ list!!38 ++ " " ++ list!!39
            print x
            let x = list!!41 ++ " " ++ list!!42 ++ " " ++ list!!43
            print x
            print " "


            let x = list!!52 ++ " " ++ list!!53 ++ " " ++ list!!54 ++ " " ++ list!!55 ++ " " ++ list!!45
            print x
            let x = list!!57 ++ " " ++ list!!58 ++ " " ++ list!!59 ++ " " ++ list!!60 ++ " " ++ list!!61
            print x
            let x = list!!63 ++ " " ++ list!!64 ++ " " ++ list!!65
            print x
            print " "


            let x = list!!74 ++ " " ++ list!!75 ++ " " ++ list!!76 ++ " " ++ list!!77 ++ " " ++ list!!67
            print x
            let x = list!!79 ++ " " ++ list!!80 ++ " " ++ list!!81 ++ " " ++ list!!82 ++ " " ++ list!!83
            print x
            let x = list!!85 ++ " " ++ list!!86 ++ " " ++ list!!87
            print x
            print " "


            let x = list!!96 ++ " " ++ list!!97 ++ " " ++ list!!98 ++ " " ++ list!!99 ++ " " ++ list!!89
            print x
            let x = list!!101 ++ " " ++ list!!102 ++ " " ++ list!!103 ++ " " ++ list!!104 ++ " " ++ list!!105
            print x
            let x = list!!106 ++ " " ++ list!!107 ++ " " ++ list!!108
            print x
            print " "

    case compare y "1" of
        LT -> do print " "
        GT -> do print " "

        EQ -> do
            print "Ruby Tasks"
            print " "

            let x = list!!117 ++ " " ++ list!!118 ++ " " ++ list!!119 ++ " " ++ list!!120 ++ " " ++ list!!110
            print x
            let x = list!!122 ++ " " ++ list!!123 ++ " " ++ list!!124 ++ " " ++ list!!125 ++ " " ++ list!!126
            print x
            let x = list!!127 ++ " " ++ list!!128 ++ " " ++ list!!129
            print x
            print " "

            let x = list!!138 ++ " " ++ list!!139 ++ " " ++ list!!140 ++ " " ++ list!!141 ++ " " ++ list!!131
            print x
            let x = list!!143 ++ " " ++ list!!144 ++ " " ++ list!!145 ++ " " ++ list!!146 ++ " " ++ list!!147
            print x
            let x = list!!148 ++ " " ++ list!!149 ++ " " ++ list!!150
            print x
            print " "

            let x = list!!159 ++ " " ++ list!!160 ++ " " ++ list!!161 ++ " " ++ list!!162 ++ " " ++ list!!152
            print x
            let x = list!!164 ++ " " ++ list!!165 ++ " " ++ list!!166 ++ " " ++ list!!167 ++ " " ++ list!!168
            print x
            let x = list!!169 ++ " " ++ list!!170 ++ " " ++ list!!171
            print x
            print " "

            let x = list!!180 ++ " " ++ list!!181 ++ " " ++ list!!182 ++ " " ++ list!!183 ++ " " ++ list!!173
            print x
            let x = list!!185 ++ " " ++ list!!186 ++ " " ++ list!!187 ++ " " ++ list!!188 ++ " " ++ list!!189
            print x
            let x = list!!190 ++ " " ++ list!!191 ++ " " ++ list!!192
            print x
            print " "

    case compare y "2" of
        LT -> do print " "
        GT -> do print " "

        EQ -> do
            print "Haskell Tasks"
            print " "

            let x = list!!201 ++ " " ++ list!!202 ++ " " ++ list!!203 ++ " " ++ list!!204 ++ " " ++ list!!194
            print x
            let x = list!!206 ++ " " ++ list!!207 ++ " " ++ list!!208 ++ " " ++ list!!209 ++ " " ++ list!!210
            print x
            let x = list!!211 ++ " " ++ list!!212 ++ " " ++ list!!213
            print x
            print " "

            let x = list!!222 ++ " " ++ list!!223 ++ " " ++ list!!224 ++ " " ++ list!!225 ++ " " ++ list!!215
            print x
            let x = list!!227 ++ " " ++ list!!228 ++ " " ++ list!!229 ++ " " ++ list!!230 ++ " " ++ list!!231
            print x
            let x = list!!232 ++ " " ++ list!!233 ++ " " ++ list!!234
            print x
            print " "

            let x = list!!243 ++ " " ++ list!!244 ++ " " ++ list!!245 ++ " " ++ list!!246 ++ " " ++ list!!236
            print x
            let x = list!!248 ++ " " ++ list!!249 ++ " " ++ list!!250 ++ " " ++ list!!251 ++ " " ++ list!!252
            print x
            let x = list!!253 ++ " " ++ list!!254 ++ " " ++ list!!255
            print x
            print " "
