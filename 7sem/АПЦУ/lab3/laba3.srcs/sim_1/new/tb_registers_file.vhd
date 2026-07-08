----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 29.09.2025 00:31:04
-- Design Name: 
-- Module Name: tb_registers_file - Behavioral
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
use std.textio.all;
use ieee.std_logic_textio.all;

entity tb_registers is
end tb_registers;

architecture Behavioral of tb_registers is
    component registers
        Port (
            S0, S1, SR, SL, CLK, CLR, OE1, OE2 : in std_logic;
            A_in, B_in, C_in, D_in, E_in, F_in, G_in, H_in : in std_logic;
            A_out, B_out, C_out, D_out, E_out, F_out, G_out, H_out : out std_logic
        );
    end component;

    -- Signals
    signal S0, S1, SR, SL, CLK, CLR, OE1, OE2 : std_logic := '0';
    signal A_in, B_in, C_in, D_in, E_in, F_in, G_in, H_in : std_logic := '0';
    signal A_out, B_out, C_out, D_out, E_out, F_out, G_out, H_out : std_logic;

    file input_buf : text;

begin
    UUT: registers
        port map(
            S0 => S0, S1 => S1, SR => SR, SL => SL, CLK => CLK, CLR => CLR,
            OE1 => OE1, OE2 => OE2,
            A_in => A_in, B_in => B_in, C_in => C_in, D_in => D_in,
            E_in => E_in, F_in => F_in, G_in => G_in, H_in => H_in,
            A_out => A_out, B_out => B_out, C_out => C_out, D_out => D_out,
            E_out => E_out, F_out => F_out, G_out => G_out, H_out => H_out
        );

    stimulus: process
        variable read_input : line;
        variable line_num : integer := 0;
        variable S0_file, S1_file, SR_file, SL_file, CLK_file, CLR_file : std_logic;
        variable OE1_file, OE2_file : std_logic;
        variable A_in_file, B_in_file, C_in_file, D_in_file : std_logic;
        variable E_in_file, F_in_file, G_in_file, H_in_file : std_logic;
        variable A_out_file, B_out_file, C_out_file, D_out_file : std_logic;
        variable E_out_file, F_out_file, G_out_file, H_out_file : std_logic;
    begin
        file_open(input_buf, "D:\lab2_test.txt", read_mode);
        
        while not endfile(input_buf) loop
            line_num := line_num + 1;
            readline(input_buf, read_input);

            read(read_input, S0_file); read(read_input, S1_file);
            read(read_input, SR_file); read(read_input, SL_file);
            read(read_input, CLK_file); read(read_input, CLR_file);
            read(read_input, OE1_file); read(read_input, OE2_file);
            read(read_input, A_in_file); read(read_input, B_in_file);
            read(read_input, C_in_file); read(read_input, D_in_file);
            read(read_input, E_in_file); read(read_input, F_in_file);
            read(read_input, G_in_file); read(read_input, H_in_file);

            read(read_input, A_out_file); read(read_input, B_out_file);
            read(read_input, C_out_file); read(read_input, D_out_file);
            read(read_input, E_out_file); read(read_input, F_out_file);
            read(read_input, G_out_file); read(read_input, H_out_file);

            S0 <= S0_file; S1 <= S1_file; SR <= SR_file; SL <= SL_file;
            CLK <= CLK_file; CLR <= CLR_file; OE1 <= OE1_file; OE2 <= OE2_file;
            A_in <= A_in_file; B_in <= B_in_file; C_in <= C_in_file; D_in <= D_in_file;
            E_in <= E_in_file; F_in <= F_in_file; G_in <= G_in_file; H_in <= H_in_file;

            wait for 5 ns;

            -- ???????? ???????
            if A_out /= A_out_file then
                report "Line " & integer'image(line_num) & ": A_out mismatch. Expected=" &
                       std_logic'image(A_out_file) & " Got=" & std_logic'image(A_out) severity ERROR;
            end if;
            if B_out /= B_out_file then
                report "Line " & integer'image(line_num) & ": B_out mismatch. Expected=" &
                       std_logic'image(B_out_file) & " Got=" & std_logic'image(B_out) severity ERROR;
            end if;
            if C_out /= C_out_file then
                report "Line " & integer'image(line_num) & ": C_out mismatch. Expected=" &
                       std_logic'image(C_out_file) & " Got=" & std_logic'image(C_out) severity ERROR;
            end if;
            if D_out /= D_out_file then
                report "Line " & integer'image(line_num) & ": D_out mismatch. Expected=" &
                       std_logic'image(D_out_file) & " Got=" & std_logic'image(D_out) severity ERROR;
            end if;
            if E_out /= E_out_file then
                report "Line " & integer'image(line_num) & ": E_out mismatch. Expected=" &
                       std_logic'image(E_out_file) & " Got=" & std_logic'image(E_out) severity ERROR;
            end if;
            if F_out /= F_out_file then
                report "Line " & integer'image(line_num) & ": F_out mismatch. Expected=" &
                       std_logic'image(F_out_file) & " Got=" & std_logic'image(F_out) severity ERROR;
            end if;
            if G_out /= G_out_file then
                report "Line " & integer'image(line_num) & ": G_out mismatch. Expected=" &
                       std_logic'image(G_out_file) & " Got=" & std_logic'image(G_out) severity ERROR;
            end if;
            if H_out /= H_out_file then
                report "Line " & integer'image(line_num) & ": H_out mismatch. Expected=" &
                       std_logic'image(H_out_file) & " Got=" & std_logic'image(H_out) severity ERROR;
            end if;

        end loop;

        file_close(input_buf);
        wait;
    end process;

end Behavioral;
