----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 23.09.2025 23:07:11
-- Design Name: 
-- Module Name: dtrigger - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity dtrigger is
  Port(
    c : in STD_LOGIC;
    d : in STD_LOGIC;
    r : in STD_LOGIC;
    q : out STD_LOGIC;
    qn : out STD_LOGIC
  );
end dtrigger;

architecture Behavioral of dtrigger is
    signal q_reg : STD_LOGIC := '0';
begin
    process(c, r)
    begin
        if r = '0' then
            q_reg <= '0';
        elsif (c'event and c = '1') then
            q_reg <= d;
        end if;
      end process;

    q <= q_reg;
    qn <= not q_reg;

end Behavioral;
