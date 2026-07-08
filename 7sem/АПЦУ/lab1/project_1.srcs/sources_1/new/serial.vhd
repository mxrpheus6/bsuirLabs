----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12.09.2025 10:22:51
-- Design Name: 
-- Module Name: serial - Behavioral
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

entity serial is
  Port (
  not_1g, not_2g : in std_logic;
  a, b : in std_logic;
  c1_0, c1_1, c1_2, c1_3 : in std_logic;
  c2_0, c2_1, c2_2, c2_3 : in std_logic;
  y1, y2 : out std_logic
  );
end serial;

architecture Behavioral of serial is

begin
    process(a, b, not_1g, not_2g, c1_0, c1_1, c1_2, c1_3, c2_0, c2_1, c2_2, c2_3)
    begin
        y1 <= '0';
        y2 <= '0';
        
        if (not_1g = '0') then
            if (b = '0' and a = '0' and c1_0 = '1' and not_1g = '0' ) then y1 <= '1';
            elsif (b = '0' and a = '1' and c1_1 = '1' and not_1g = '0' ) then y1 <= '1';
            elsif (b = '1' and a = '0' and c1_2 = '1' and not_1g = '0' ) then y1 <= '1';
            elsif (b = '1' and a = '1' and c1_3 = '1' and not_1g = '0' ) then y1 <= '1';
            end if;
        end if;
        
        if (not_2g = '0') then
            if (b = '0' and a = '0' and c2_0 = '1' and not_2g = '0' ) then y2 <= '1';
            elsif (b = '0' and a = '1' and c2_1 = '1' and not_2g = '0' ) then y2 <= '1';
            elsif (b = '1' and a = '0' and c2_2 = '1' and not_2g = '0' ) then y2 <= '1';
            elsif (b = '1' and a = '1' and c2_3 = '1' and not_2g = '0' ) then y2 <= '1';
            end if;
        end if;
        
    end process;
end Behavioral;