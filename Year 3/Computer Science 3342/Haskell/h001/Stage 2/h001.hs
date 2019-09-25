import System.IO
import Control.Monad

main = do
    let list = []
    handle <- openFile "test.txt" ReadMode
    contents <- hGetContents handle
    let singlewords = words contents
        list = singlewords

    -- UGLY CODE BLOCK
    -- DOING THIS THE LONG WAY
    -- HOPEFULLY WILL FIX LATER
    -- ONLY PUTTING 2 TASKS FROM EACH DUE TO TIME

    -- HASKELL
    let x = list!!0 ++ " " ++ list!!1
    print x
    let x = list!!2 ++ " " ++ list!!3 ++ " " ++ list!!4 ++ " " ++ list!!5
    print x
    let x = list!!6 ++ " " ++ list!!7 ++ " " ++ list!!8 ++ " " ++ list!!9 ++ " " ++ list!!10 ++ " " ++ list!!11 ++ " " ++ list!!12
    print x
    let x = list!!13 ++ " " ++ list!!14 ++ " " ++ list!!15 ++ " " ++ list!!16 ++ " " ++ list!!17
    print x
    let x = list!!18 ++ " " ++ list!!19 ++ " " ++ list!!20 ++ " " ++ list!!21 ++ " " ++ list!!22 ++ " " ++ list!!23 ++ " " ++ list!!24
    print x
    print " "

    -- RUBY
    let x = list!!25 ++ " " ++ list!!26
    print x
    let x = list!!27 ++ " " ++ list!!28 ++ " " ++ list!!29 ++ " " ++ list!!30
    print x
    let x = list!!31 ++ " " ++ list!!32 ++ " " ++ list!!33 ++ " " ++ list!!34 ++ " " ++ list!!35 ++ " " ++ list!!36 ++ " " ++ list!!37
    print x
    let x = list!!38 ++ " " ++ list!!39 ++ " " ++ list!!40 ++ " " ++ list!!41 ++ " " ++ list!!42
    print x
    let x = list!!43 ++ " " ++ list!!44 ++ " " ++ list!!45 ++ " " ++ list!!46 ++ " " ++ list!!47 ++ " " ++ list!!48 ++ " " ++ list!!49
    print x
    print " "

    let x = list!!50 ++ " " ++ list!!51
    print x
    let x = list!!52 ++ " " ++ list!!53 ++ " " ++ list!!54 ++ " " ++ list!!55
    print x
    let x = list!!56 ++ " " ++ list!!57 ++ " " ++ list!!58 ++ " " ++ list!!59 ++ " " ++ list!!60 ++ " " ++ list!!61 ++ " " ++ list!!62
    print x
    let x = list!!63 ++ " " ++ list!!64 ++ " " ++ list!!65 ++ " " ++ list!!66 ++ " " ++ list!!67
    print x
    let x = list!!68 ++ " " ++ list!!69 ++ " " ++ list!!70
    print x
    print " "

    -- JAVASCRIPT
    let x = list!!71 ++ " " ++ list!!72
    print x
    let x = list!!73 ++ " " ++ list!!74 ++ " " ++ list!!75 ++ " " ++ list!!76
    print x
    let x = list!!77 ++ " " ++ list!!78 ++ " " ++ list!!79 ++ " " ++ list!!80 ++ " " ++ list!!81 ++ " " ++ list!!82 ++ " " ++ list!!83
    print x
    let x = list!!84 ++ " " ++ list!!85 ++ " " ++ list!!86 ++ " " ++ list!!87 ++ " " ++ list!!88
    print x
    let x = list!!90 ++ " " ++ list!!91 ++ " " ++ list!!92
    print x
    print " "


    let x = list!!93 ++ " " ++ list!!94
    print x
    let x = list!!95 ++ " " ++ list!!96 ++ " " ++ list!!97 ++ " " ++ list!!98
    print x
    let x = list!!99 ++ " " ++ list!!100 ++ " " ++ list!!101 ++ " " ++ list!!102 ++ " " ++ list!!103 ++ " " ++ list!!104 ++ " " ++ list!!105
    print x
    let x = list!!106 ++ " " ++ list!!107 ++ " " ++ list!!108 ++ " " ++ list!!109 ++ " " ++ list!!110
    print x
    let x = list!!112 ++ " " ++ list!!113 ++ " " ++ list!!114
    print x
    print " "


    hClose handle

