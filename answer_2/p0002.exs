defmodule ProjectEuler2 do
    defp even_fibsum(f1, f2, max, acc) do
        cond do
            f2 >= max -> # stop once limit is reached
                acc
            rem(f2, 2) == 0 ->
                even_fibsum(f2, f1+f2, max, acc+f2) # add up even
            true ->
                even_fibsum(f2, f1+f2, max, acc) # ignore odd
        end
    end
    defp even_fibsum_less_than(max), do: even_fibsum(1, 2, max, 0)

    def solve(), do: even_fibsum_less_than(4_000_000)
    # def solve(), do: even_fibsum_less_than(100)
end

IO.puts ProjectEuler2.solve()
