import System.IO
import Control.Monad
import System.Process
import Data.String

-- Short code for stage 1-3
-- test = readProcess "/usr/bin/git" ["log", "--author=jkaba", "--reverse"] []
-- main :: IO ()
-- main = test >>= putStrLn

args = getArgs::IO[Char]
isOpChr :: Char -> Bool

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

print"Input a type(0 for js, 1 for ruby, 2 for haskell): "
    type <- getLine

    case compare type 0 of
        LT -> do print " "
        GT -> do print " "

        EQ -> do
            print "Javascript Tasks"
            print " "

            let x = list!!0 ++ " " ++ list!!1
            print x
            let x = list!!2 ++ " " ++ list!!3 ++ " " ++ list!!4 ++ " " ++ list!!5
            print x
            let x = list!!6 ++ " " ++ list!!7 ++ " " ++ list!!8 ++ " " ++ list!!9 ++ " " ++ list!!10 ++ " " ++ list!!11 ++ " " ++ list!!12
            print x
            let x = list!!13 ++ " " ++ list!!14 ++ " " ++ list!!15 ++ " " ++ list!!16 ++ " " ++ list!!17
            print x
            let x = list!!19 ++ " " ++ list!!20 ++ " " ++ list!!21
            print x
            print " "


            let x = list!!22 ++ " " ++ list!!23
            print x
            let x = list!!24 ++ " " ++ list!!25 ++ " " ++ list!!26 ++ " " ++ list!!27
            print x
            let x = list!!28 ++ " " ++ list!!29 ++ " " ++ list!!30 ++ " " ++ list!!31 ++ " " ++ list!!32 ++ " " ++ list!!33 ++ " " ++ list!!34
            print x
            let x = list!!35 ++ " " ++ list!!36 ++ " " ++ list!!37 ++ " " ++ list!!38 ++ " " ++ list!!39
            print x
            let x = list!!41 ++ " " ++ list!!42 ++ " " ++ list!!43
            print x
            print " "


            let x = list!!44 ++ " " ++ list!!45
            print x
            let x = list!!46 ++ " " ++ list!!47 ++ " " ++ list!!48 ++ " " ++ list!!49
            print x
            let x = list!!50 ++ " " ++ list!!51 ++ " " ++ list!!52 ++ " " ++ list!!53 ++ " " ++ list!!54 ++ " " ++ list!!55 ++ " " ++ list!!56
            print x
            let x = list!!57 ++ " " ++ list!!58 ++ " " ++ list!!59 ++ " " ++ list!!60 ++ " " ++ list!!61
            print x
            let x = list!!63 ++ " " ++ list!!64 ++ " " ++ list!!65
            print x
            print " "


            let x = list!!66 ++ " " ++ list!!67
            print x
            let x = list!!68 ++ " " ++ list!!69 ++ " " ++ list!!70 ++ " " ++ list!!71
            print x
            let x = list!!72 ++ " " ++ list!!73 ++ " " ++ list!!74 ++ " " ++ list!!75 ++ " " ++ list!!76 ++ " " ++ list!!77 ++ " " ++ list!!78
            print x
            let x = list!!79 ++ " " ++ list!!80 ++ " " ++ list!!81 ++ " " ++ list!!82 ++ " " ++ list!!83
            print x
            let x = list!!85 ++ " " ++ list!!86 ++ " " ++ list!!87
            print x
            print " "


            let x = list!!88 ++ " " ++ list!!89
            print x
            let x = list!!90 ++ " " ++ list!!91 ++ " " ++ list!!92 ++ " " ++ list!!93
            print x
            let x = list!!94 ++ " " ++ list!!95 ++ " " ++ list!!96 ++ " " ++ list!!97 ++ " " ++ list!!98 ++ " " ++ list!!99 ++ " " ++ list!!100
            print x
            let x = list!!101 ++ " " ++ list!!102 ++ " " ++ list!!103 ++ " " ++ list!!104 ++ " " ++ list!!105
            print x
            let x = list!!106 ++ " " ++ list!!107 ++ " " ++ list!!108
            print x
            print " "

    case compare type 1 of
        LT -> do print " "
        GT -> do print " "

        EQ -> do
            print "Ruby Tasks"
            print " "


            let x = list!!109 ++ " " ++ list!!110
            print x
            let x = list!!111 ++ " " ++ list!!112 ++ " " ++ list!!113 ++ " " ++ list!!114
            print x
            let x = list!!115 ++ " " ++ list!!116 ++ " " ++ list!!117 ++ " " ++ list!!118 ++ " " ++ list!!119 ++ " " ++ list!!120 ++ " " ++ list!!121
            print x
            let x = list!!122 ++ " " ++ list!!123 ++ " " ++ list!!124 ++ " " ++ list!!125 ++ " " ++ list!!126
            print x
            let x = list!!127 ++ " " ++ list!!128 ++ " " ++ list!!129
            print x
            print " "


            let x = list!!130 ++ " " ++ list!!131
            print x
            let x = list!!132 ++ " " ++ list!!133 ++ " " ++ list!!134 ++ " " ++ list!!135
            print x
            let x = list!!136 ++ " " ++ list!!137 ++ " " ++ list!!138 ++ " " ++ list!!139 ++ " " ++ list!!140 ++ " " ++ list!!141 ++ " " ++ list!!142
            print x
            let x = list!!143 ++ " " ++ list!!144 ++ " " ++ list!!145 ++ " " ++ list!!146 ++ " " ++ list!!147
            print x
            let x = list!!148 ++ " " ++ list!!149 ++ " " ++ list!!150
            print x
            print " "


            let x = list!!151 ++ " " ++ list!!152
            print x
            let x = list!!153 ++ " " ++ list!!154 ++ " " ++ list!!155 ++ " " ++ list!!156
            print x
            let x = list!!157 ++ " " ++ list!!158 ++ " " ++ list!!159 ++ " " ++ list!!160 ++ " " ++ list!!161 ++ " " ++ list!!162 ++ " " ++ list!!163
            print x
            let x = list!!164 ++ " " ++ list!!165 ++ " " ++ list!!166 ++ " " ++ list!!167 ++ " " ++ list!!168
            print x
            let x = list!!169 ++ " " ++ list!!170 ++ " " ++ list!!171
            print x
            print " "


            let x = list!!172 ++ " " ++ list!!173
            print x
            let x = list!!174 ++ " " ++ list!!175 ++ " " ++ list!!176 ++ " " ++ list!!177
            print x
            let x = list!!178 ++ " " ++ list!!179 ++ " " ++ list!!180 ++ " " ++ list!!181 ++ " " ++ list!!182 ++ " " ++ list!!183 ++ " " ++ list!!184
            print x
            let x = list!!185 ++ " " ++ list!!186 ++ " " ++ list!!187 ++ " " ++ list!!188 ++ " " ++ list!!189
            print x
            let x = list!!190 ++ " " ++ list!!191 ++ " " ++ list!!192
            print x
            print " "

    case compare type 2 of
        LT -> do print " "
        GT -> do print " "

        EQ -> do
            print "Haskell Tasks"
            print " "

            let x = list!!193 ++ " " ++ list!!194
            print x
            let x = list!!195 ++ " " ++ list!!196 ++ " " ++ list!!197 ++ " " ++ list!!198
            print x
            let x = list!!199 ++ " " ++ list!!200 ++ " " ++ list!!201 ++ " " ++ list!!202 ++ " " ++ list!!203 ++ " " ++ list!!204 ++ " " ++ list!!205
            print x
            let x = list!!206 ++ " " ++ list!!207 ++ " " ++ list!!208 ++ " " ++ list!!209 ++ " " ++ list!!210
            print x
            let x = list!!211 ++ " " ++ list!!212 ++ " " ++ list!!213
            print x
            print " "


            let x = list!!214 ++ " " ++ list!!215
            print x
            let x = list!!216 ++ " " ++ list!!217 ++ " " ++ list!!218 ++ " " ++ list!!219
            print x
            let x = list!!220 ++ " " ++ list!!221 ++ " " ++ list!!222 ++ " " ++ list!!223 ++ " " ++ list!!224 ++ " " ++ list!!225 ++ " " ++ list!!226
            print x
            let x = list!!227 ++ " " ++ list!!228 ++ " " ++ list!!229 ++ " " ++ list!!230 ++ " " ++ list!!231
            print x
            let x = list!!232 ++ " " ++ list!!233 ++ " " ++ list!!234
            print x
            print " "


            let x = list!!235 ++ " " ++ list!!236
            print x
            let x = list!!237 ++ " " ++ list!!238 ++ " " ++ list!!239 ++ " " ++ list!!240
            print x
            let x = list!!241 ++ " " ++ list!!242 ++ " " ++ list!!243 ++ " " ++ list!!244 ++ " " ++ list!!245 ++ " " ++ list!!246 ++ " " ++ list!!247
            print x
            let x = list!!248 ++ " " ++ list!!249 ++ " " ++ list!!250 ++ " " ++ list!!251 ++ " " ++ list!!252
            print x
            let x = list!!253 ++ " " ++ list!!254 ++ " " ++ list!!255
            print x
            print " "
