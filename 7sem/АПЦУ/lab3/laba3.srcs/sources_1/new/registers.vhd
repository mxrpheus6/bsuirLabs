library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity registers is
    Port (
        S0   : in  std_logic;
        S1   : in  std_logic;
        SR   : in  std_logic;
        SL   : in  std_logic;
        CLK  : in  std_logic;
        CLR  : in  std_logic;
        OE1  : in  std_logic;
        OE2  : in  std_logic;
        A_in : in  std_logic;
        B_in : in  std_logic;
        C_in : in  std_logic;
        D_in : in  std_logic;
        E_in : in  std_logic;
        F_in : in  std_logic;
        G_in : in  std_logic;
        H_in : in  std_logic;
        A_out : out std_logic;
        B_out : out std_logic;
        C_out : out std_logic;
        D_out : out std_logic;
        E_out : out std_logic;
        F_out : out std_logic;
        G_out : out std_logic;
        H_out : out std_logic
    );
end registers;

architecture Behavioral of registers is
    component dtrigger
    Port(
        c : in STD_LOGIC;
        d : in STD_LOGIC;
        r : in STD_LOGIC;
        q : out STD_LOGIC;
        qn : out STD_LOGIC
    );
    end component;
    
    signal D_A, D_B, D_C, D_D, D_E, D_F, D_G, D_H : STD_LOGIC;
    signal Q_A, Q_B, Q_C, Q_D, Q_E, Q_F, Q_G, Q_H : STD_LOGIC;
    signal nQ_A, nQ_B, nQ_C, nQ_D, nQ_E, nQ_F, nQ_G, nQ_H : STD_LOGIC;
    signal output_enable : STD_LOGIC;
       
begin

    output_enable <= OE1 AND OE2;

    FF0 : dtrigger port map (c => CLK, d => D_A, r => CLR, q => Q_A, qn => nQ_A);
    FF1 : dtrigger port map (c => CLK, d => D_B, r => CLR, q => Q_B, qn => nQ_B);
    FF2 : dtrigger port map (c => CLK, d => D_C, r => CLR, q => Q_C, qn => nQ_C);
    FF3 : dtrigger port map (c => CLK, d => D_D, r => CLR, q => Q_D, qn => nQ_D);    
    FF4 : dtrigger port map (c => CLK, d => D_E, r => CLR, q => Q_E, qn => nQ_E);
    FF5 : dtrigger port map (c => CLK, d => D_F, r => CLR, q => Q_F, qn => nQ_F);
    FF6 : dtrigger port map (c => CLK, d => D_G, r => CLR, q => Q_G, qn => nQ_G);
    FF7 : dtrigger port map (c => CLK, d => D_H, r => CLR, q => Q_H, qn => nQ_H);

    D_A <= (SR AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND Q_B) OR
           (S1 AND S0 AND A_in) OR
           (NOT S1 AND NOT S0 AND Q_A);
           
    D_B <= (Q_A AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND Q_C) OR
           (S1 AND S0 AND B_in) OR
           (NOT S1 AND NOT S0 AND Q_B);

    D_C <= (Q_B AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND Q_D) OR
           (S1 AND S0 AND C_in) OR
           (NOT S1 AND NOT S0 AND Q_C);
        
    D_D <= (Q_C AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND Q_E) OR
           (S1 AND S0 AND D_in) OR
           (NOT S1 AND NOT S0 AND Q_D);

    D_E <= (Q_D AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND Q_F) OR
           (S1 AND S0 AND E_in) OR
           (NOT S1 AND NOT S0 AND Q_E);

    D_F <= (Q_E AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND Q_G) OR
           (S1 AND S0 AND F_in) OR
           (NOT S1 AND NOT S0 AND Q_F);
            
    D_G <= (Q_F AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND Q_H) OR
           (S1 AND S0 AND G_in) OR
           (NOT S1 AND NOT S0 AND Q_G);
           
    D_H <= (Q_G AND S0 AND NOT S1) OR
           (S1 AND NOT S0 AND SL) OR
           (S1 AND S0 AND H_in) OR
           (NOT S1 AND NOT S0 AND Q_H);

    A_out <= Q_A when output_enable = '1' else 'Z';
    B_out <= Q_B when output_enable = '1' else 'Z';
    C_out <= Q_C when output_enable = '1' else 'Z';
    D_out <= Q_D when output_enable = '1' else 'Z';
    E_out <= Q_E when output_enable = '1' else 'Z';
    F_out <= Q_F when output_enable = '1' else 'Z';
    G_out <= Q_G when output_enable = '1' else 'Z';
    H_out <= Q_H when output_enable = '1' else 'Z';

end Behavioral;