----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11.09.2025 23:00:55
-- Design Name: 
-- Module Name: parallel_tb - Behavioral
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

entity parallel_tb is
--  Port ( );
end parallel_tb;

architecture Behavioral of parallel_tb is
    -- Объявляем компонент для тестирования
    component parallel
        Port (
            not_1g, not_2g : in std_logic;
            a, b : in std_logic;
            c1_0, c1_1, c1_2, c1_3 : in std_logic;
            c2_0, c2_1, c2_2, c2_3 : in std_logic;
            y1, y2 : out std_logic
        );
    end component;

    -- Сигналы для подключения к тестируемому устройству
    signal not_1g, not_2g : std_logic;
    signal a, b : std_logic;
    signal c1_0, c1_1, c1_2, c1_3 : std_logic;
    signal c2_0, c2_1, c2_2, c2_3 : std_logic;
    signal y1, y2 : std_logic;

begin
    -- Создаем экземпляр тестируемого устройства
    uut: parallel port map (
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

    -- Процесс тестирования
    stimulus: process
    begin
        -- Тест 1: Проверка когда оба выхода отключены
        not_1g <= '1'; not_2g <= '1';  -- Оба выхода отключены
        a <= '0'; b <= '0';
        c1_0 <= '1'; c1_1 <= '0'; c1_2 <= '1'; c1_3 <= '0';
        c2_0 <= '0'; c2_1 <= '1'; c2_2 <= '0'; c2_3 <= '1';
        wait for 10 ns;
        
        -- Тест 2: Включен только первый мультиплексор
        not_1g <= '0'; not_2g <= '1';
        a <= '0'; b <= '0';  -- Выбираем c1_0
        wait for 10 ns;
        
        a <= '1'; b <= '0';  -- Выбираем c1_1
        wait for 10 ns;
        
        a <= '0'; b <= '1';  -- Выбираем c1_2
        wait for 10 ns;
        
        a <= '1'; b <= '1';  -- Выбираем c1_3
        wait for 10 ns;
        
        -- Тест 3: Включен только второй мультиплексор
        not_1g <= '1'; not_2g <= '0';
        a <= '0'; b <= '0';  -- Выбираем c2_0
        wait for 10 ns;
        
        a <= '1'; b <= '0';  -- Выбираем c2_1
        wait for 10 ns;
        
        a <= '0'; b <= '1';  -- Выбираем c2_2
        wait for 10 ns;
        
        a <= '1'; b <= '1';  -- Выбираем c2_3
        wait for 10 ns;
        
        -- Тест 4: Оба мультиплексора включены
        not_1g <= '0'; not_2g <= '0';
        a <= '0'; b <= '0';  -- Выбираем c1_0 и c2_0
        wait for 10 ns;
        
        a <= '1'; b <= '1';  -- Выбираем c1_3 и c2_3
        wait for 10 ns;
        
        -- Добавляем проверку разных значений на входах
        c1_0 <= '0'; c1_1 <= '1'; c1_2 <= '0'; c1_3 <= '1';
        c2_0 <= '1'; c2_1 <= '0'; c2_2 <= '1'; c2_3 <= '0';
        a <= '0'; b <= '1';
        wait for 10 ns;
        
        -- Завершаем симуляцию
        wait;
    end process stimulus;

end Behavioral;
