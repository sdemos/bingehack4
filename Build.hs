import Development.Shake
import Development.Shake.Command
import Development.Shake.FilePath
import Development.Shake.Util

clang = "clang"
buildDir = "_build"
outDir = buildDir </> "out"
includeDirs = [ "libnethack/include"
              , "nethack/include"
              , "libnethack_common/include"
              , "libnethack_client/include"
              , "libuncursed/include"
              ]

data LinkResult = Executable
                | Library

compile :: CmdResult r
        => [String] -- include directories
        -> String   -- source file
        -> String   -- object file
        -> Action r
compile includes src obj = command [] clang (iflags ++ ["-o", obj, "-c", src])
    where iflags = map ("-I"++) includes

link :: CmdResult r
     => LinkResult -- type of linking to perform
     -> [String]   -- directories to add to linker search path
     -> [String]   -- libraries to link against
     -> [String]   -- object files to link
     -> String     -- name of result
     -> Action r
link ty ldirs libs objs result =
    command [] clang (linkflag ++ lpaths ++ llibs ++ ["-o", result] ++ objs)
    where lpaths = map ("-L"++) ldirs
          llibs = map ("-l"++) libs
          linkflag = case ty of Executable -> []
                                Library    -> ["-shared"]

build :: LinkResult        -- type of build
      -> FilePath          -- name of executable
      -> [String]          -- libraries to link against
      -> [String]          -- libraries to link against that we have to build
      -> Action [FilePath] -- files to compile and link
      -> Rules ()
build ty result libs nlibs getSources = do
    let needLibs = map (\l -> (outDir </> "lib") ++ l ++ ".so") nlibs
    outDir </> result %> \out -> do
        sources <- getSources
        let objs = [ buildDir </> s -<.> "o" | s <- sources ]
        need (objs ++ needLibs)
        link ty [outDir] (libs ++ nlibs) objs out

library = build Library
executable = build Executable

main :: IO ()
main = shakeArgs shakeOptions { shakeFiles = buildDir } $ do
    want [outDir </> "nethack"]
    library "libuncursed.so" [] [] (getDirectoryFiles "" ["libuncursed/src//*.c"])
    library "libnethack_common.so" [] [] (getDirectoryFiles "" ["libnethack_common/src//*.c"])
    library "libnethack.so" ["z"] ["nethack_common"] (getDirectoryFiles "" ["libnethack/src//*.c"])
    library "libnethack_client.so" ["jansson"] ["nethack_common"] (getDirectoryFiles "" ["libnethack_client/src//*.c"])
    executable "nethack" ["jansson"] ["nethack", "nethack_common", "nethack_client", "uncursed"] (getDirectoryFiles "" ["nethack/src//*.c"])

    buildDir </> "//*.o" %> \obj -> do
        let source = dropDirectory1 obj -<.> "c"
        compile includeDirs source obj
