import System.IO
import Data.Char
import Control.Monad
import Data.Ord
import Data.List as L
import Numeric

import Debug.Trace


main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    t <- fmap read getLine :: IO Int
    forM_ [1..t] $ \ c -> do
        hPrint stderr c
        [n, k] <- fmap (fmap read . words) getLine :: IO [Int]
        pks <- replicateM n $ do
            [r, h] <- fmap (fmap read . words) getLine :: IO [Int]
            return (r, h)
        let ans = solve k pks
        putStrLn $ "Case #" ++ show c ++ ": " ++ showFFloat Nothing ans ""


harea :: (Int, Int) -> Double
harea (r, h) = fromRational $ 2 * toRational pi * toRational r * toRational h


totalarea :: [(Int, Int)] -> Double
totalarea (pk:pks) = ((fromRational $ toRational pi *r*r) :: Double) + harea pk + sum (map harea pks)
    where
        r = toRational $ fst pk
        h = toRational $ snd pk



bestFor :: Int -> [(Int, Int)] -> Double
-- bestFor k (pk:pks) = totalarea $ traceShow (pk, pks, sol, totalarea sol) sol
bestFor k (pk:pks) = totalarea sol
    where
        pksvalid = filter ( \ (rr, _) -> rr <= fst pk ) pks
        bestpks = L.sortBy (flip (comparing harea)) pksvalid
        sol = pk : take (k - 1) bestpks


solve :: Int -> [(Int, Int)] -> Double
solve k pks = maximum $ map (bestFor k) rotations
    where
        -- rotations = traceShow (k, rots) rots
        rotations = rots
        rots = map rot [0..(length pks - 1)]
        rot n = suff ++ pref
            where (pref, suff) = splitAt n pks
