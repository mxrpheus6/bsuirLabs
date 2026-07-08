----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 29.09.2025 00:24:12
-- Design Name: 
-- Module Name: tb_parallel_file - Behavioral
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
use STD.TEXTIO.ALL;
use IEEE.STD_LOGIC_TEXTIO.ALL;

entity tb_parallel_file is
end tb_parallel_file;

architecture Behavioral of tb_parallel_file is
    component parallel
        Port (
            not_1g, not_2g : in std_logic;
            a, b : in std_logic;
            c1_0, c1_1, c1_2, c1_3 : in std_logic;
            c2_0, c2_1, c2_2, c2_3 : in std_logic;
            y1, y2 : out std_logic
        );
    end component;

    -- signals
    signal not_1g, not_2g : std_logic;
    signal a, b : std_logic;
    signal c1_0, c1_1, c1_2, c1_3 : std_logic;
    signal c2_0, c2_1, c2_2, c2_3 : std_logic;
    signal y1, y2 : std_logic;
    
    file input_buf : text;

begin
    UUT: parallel
        port map (
            not_1g => not_1g,
            not_2g => not_2g,
            a => a,
            b => b,
            c1_0 => c1_0,
            c1_1 => c1_1,
            c1_2 => c1_2,
            c1_3 => c1_3,
            c2_0 => c2_0,
            c2_1 => c2_1,
            c2_2 => c2_2,
            c2_3 => c2_3,
            y1 => y1,
            y2 => y2
        );


    stimulus: process
        variable read_input : line;
        variable line_num : integer := 0;
        variable not_1g_file, not_2g_file : std_logic;
        variable a_file, b_file : std_logic;
        variable c1_0_file, c1_1_file, c1_2_file, c1_3_file : std_logic;
        variable c2_0_file, c2_1_file, c2_2_file, c2_3_file : std_logic;
        variable y1_file, y2_file : std_logic;
    begin
        file_open(input_buf, "D:\lab1_test.txt", read_mode);
        
        while not endfile(input_buf) loop
            line_num := line_num + 1;
            readline(input_buf, read_input);
            
            read(read_input, not_1g_file);
            read(read_input, not_2g_file);
            read(read_input, a_file);
            read(read_input, b_file);
            
            read(read_input, c1_0_file);
            read(read_input, c1_1_file);
            read(read_input, c1_2_file);
            read(read_input, c1_3_file);
            
            read(read_input, c2_0_file);
            read(read_input, c2_1_file);
            read(read_input, c2_2_file);
            read(read_input, c2_3_file);
            
            read(read_input, y1_file);
            read(read_input, y2_file);
            
            not_1g <= not_1g_file;
            not_2g <= not_2g_file;
            a <= a_file;
            b <= b_file;
            c1_0 <= c1_0_file;
            c1_1 <= c1_1_file;
            c1_2 <= c1_2_file;
            c1_3 <= c1_3_file;
            c2_0 <= c2_0_file;
            c2_1 <= c2_1_file;
            c2_2 <= c2_2_file;
            c2_3 <= c2_3_file;
            
            wait for 5 ns;
            
            if y1 /= y1_file then
                report "Line " & integer'image(line_num) & ": y1 not equal to its file value" severity ERROR;
            end if;
            if y2 /= y2_file then
                report "Line " & integer'image(line_num) & ": y2 not equal to its file value" severity ERROR;
            end if;
        end loop;
        
        file_close(input_buf);
        wait;
    end process;
end Behavioral;

