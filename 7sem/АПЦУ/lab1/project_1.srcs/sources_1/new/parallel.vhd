----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11.09.2025 09:04:49
-- Design Name: 
-- Module Name: parallel - Behavioral
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

entity parallel is
  Port (
    not_1g, not_2g : in std_logic;
    a, b : in std_logic;
    c1_0, c1_1, c1_2, c1_3 : in std_logic;
    c2_0, c2_1, c2_2, c2_3 : in std_logic;
    y1, y2 : out std_logic
    );
end parallel;

architecture Behavioral of parallel is
begin
    
    y1 <= not not_1g and ((not b and not a and c1_0) or 
                         (not b and a and c1_1) or 
                         (b and not a and c1_2) or 
                         (b and a and c1_3));
                         
    y2 <= not not_2g and ((not b and not a and c2_0) or 
                         (not b and a and c2_1) or 
                         (b and not a and c2_2) or 
                         (b and a and c2_3));

end Behavioral;
