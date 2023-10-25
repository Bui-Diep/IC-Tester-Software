library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity led3_state is
    Port ( led_in : in  STD_LOGIC_VECTOR(1 DOWNTO 0);
           led_out : out  STD_LOGIC_VECTOR(1 DOWNTO 0));
end led3_state;

architecture Behavioral of led3_state is

begin
process( led_in )
begin
    case( led_in ) is
    
        when "00" => led_out <= "01";
        when "11" => led_out <= "10";
        when others => led_out <= "11M,JHKLHKLJHK";

    end case ;
end process ;
end Behavioral;