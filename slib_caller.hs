#!/usr/bin/env runghc
import Foreign.Ptr
import System.Environment
import System.Posix.DynamicLinker

showUsage = do
    progname <- getProgName
    putStrLn $ "Usage: " ++ progname ++ " foo.so [function_name]"

-- https://downloads.haskell.org/~ghc/6.12.2/docs/html/libraries/base-4.2.0.1/Foreign-Ptr.html#2
foreign import ccall "dynamic"
    callCFunc :: FunPtr () -> (IO ())

doDynamicFuncall libname fnname = withDL libname [RTLD_NOW] (\dl -> dlsym dl fnname >>= callCFunc)

main = do
    args <- getArgs
    case args of
        [libname] -> doDynamicFuncall libname "function1"
        [libname, fnname] -> doDynamicFuncall libname fnname
        _ -> showUsage
