defmodule ProjectEuler3 do
    defp largest_prime_factor(n, f) do
        if rem(n, f) == 0 do
            if div(n, f) <= f do
                f
            else
                largest_prime_factor(div(n, f), f+1)
            end
        else
            largest_prime_factor(n, f+1)
        end
    end
    defp largest_prime_factor(n), do: largest_prime_factor(n, 2)

    def solve(), do: largest_prime_factor(600851475143)
    # def solve(), do: largest_prime_factor(13195)
    # def solve(), do: largest_prime_factor(15)
end

IO.puts ProjectEuler3.solve()
