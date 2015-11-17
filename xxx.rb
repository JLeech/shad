class Player
  attr_accessor :value
  attr_accessor :place

  def initialize(value,place)
    @value = value
    @place = place
  end 

  def self.sum_values(players)
    sum = 0  
    players.each { |player| sum += player.value }
    return sum
  end

  def self.get_places(players)
    players.map { |player| player.place } 
  end

end

def get_random_set(size)
  set = []
  (0..size-1).each { |place| set.push( Player.new(rand(80),place)) }
  return set
end

def get_player_for_values(values)
  set = []
  values.each_with_index { |value,iter| set.push(Player.new(value,iter+1)) }
  return set
end

def recombine_set(set,player)
  head_sum = 0
  delete_till = 0
  set.each_with_index do |in_team, index|
    head_sum += in_team
    next if index == 0
    if index == set.size-1
      set << player
      set.shift(delete_till+1)
      break
    end
    if set[index]+set[index+1] > player
      set << player
      set.shift(delete_till)
      break
    else
      deleted_value = set[0]
      head_sum += deleted_value
      delete_till += 1
    end
  end
  return set
end

def casual_algo(set)
  set = set.sort { |a,b| a.value <=> b.value }
  current_max_value = 0
  lowest_sum = 0
  current_team = []
  set.each do |player|
    if current_team.length <= 2
      current_team <= player
    else
      if lowest_sum >= player.value
        current_team << player
        current_max_value +=player.value
      else
        set = recombine_set(set,player)
      end 
    end
  end
  
end



def brute_algo(set)
  max_set_value = 0
  max_set_position = 0
  set.each_with_index do |comb,iter|
    comb = comb.sort { |a,b| a.value <=> b.value }
    if comb.length > 1 && Player.sum_values([comb[0],comb[1]]) >= comb.last.value
      set_value = Player.sum_values(comb)
      if  set_value > max_set_value
        max_set_position = iter
        max_set_value = set_value
      end
    end
  end
  puts Player.get_places(set[max_set_position])
end

size = 5
#sorted_players = get_random_set(size).sort { |a,b| a.value <=> b.value }.map { |player| player.value }
#players = get_random_set(size)
#players = get_player_for_values([1, 2, 4, 8, 16])
#combined_players = (0..size).flat_map{ |cur_size| players.combination(cur_size).to_a } 
#puts "#{combined_players.map { |comb| comb.map { |player| player.value } } }"
#brute_algo(combined_players)
#casual_algo(players)
puts recombine_set([1,2,4,8],16)