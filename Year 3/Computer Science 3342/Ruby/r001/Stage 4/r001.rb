class KnownTasks
  def initialize(known_task_file_name)
   @tasks = Array.new
   IO.read(known_task_file_name).each_line do | line |
      @tasks.push(line.delete("\n"))
   end
  end
  def known?(task_name)
    @tasks.include?(task_name)
  end
  def print(config)
    @tasks.each do | line |
      config.putsq line
    end
  end
end

class LogEntry
  include Comparable
  def <=>(other)
    @commit_id <=> other.commit_id
  end

  def initialize(config, entry_string, known_tasks, logger, jstasks, rubtasks)
    entry_array = entry_string.split
    @commit_id = entry_array[0]
    
    if not(entry_string.include?('jkaba'))
        if(entry_string.include?('j001') || entry_string.include?('j002') || entry_string.include?('j100') || entry_string.include?('j200'))
            jstasks.push(entry_string)
        end
        
        if(entry_string.include?('r001'))
            rubtasks.push(entry_string)
        end
        
        logger.push(entry_string)
    end
  end
end

class GitLog
  def initialize(config, git_log_source, known_tasks = nil)
    if git_log_source.class == Array then
      @git_log = git_log_source
      return
    end
    
    @logger = Array.new
    @newlogger = Array.new
    @jstasks = Array.new
    @rubtasks = Array.new
    @copy = Array.new
    @coper = Array.new
    @git_log = Array.new
    
    git_log_source.each_line do | line |
        @git_log.push(LogEntry.new(config, line, known_tasks, @logger, @jstasks, @rubtasks))
    end
    
    i = 0
    j = 0
    k = @logger.length() - 1
    
    puts "\nJAVASCRIPT TASKS\n\n"
    for i in 0..k
        if(@logger.at(i) == @jstasks.at(j))
            puts @logger[i-3]
            puts @logger[i-2]
            puts "\n"
            puts @logger[i]
            puts @logger[i+1]
            puts "\n"
            j = j + 1
        end
    end
    
    j = 0
    puts "\nRUBY TASKS\n\n"
    for i in 0..k
        if(@logger.at(i) == @rubtasks.at(j))
            puts @logger[i-3]
            puts @logger[i-2]
            puts "\n"
            puts @logger[i]
            puts @logger[i+1]
            puts "\n"
            j = j + 1
        end
    end
  
  end
  def include?(entry)
    @git_log.include?(entry)
  end
end

class NewLog
  def initialize(config, known_tasks)
    stdout = `git log --reverse --author=jkaba`
    @git_log = GitLog.new(config, stdout, known_tasks)
  end
  def print(config)
    @git_log.print(config)
  end
end

class Summary
  attr_accessor :date, :report_type, :quiet, :error_out, :git_from_file
  def initialize(arg_list)
    @error_out = STDERR
  end
  def putsq(message)
    puts message unless @quiet
  end
  def puterr(message)
    @error_out.puts message
  end
end

config = Summary.new(ARGV)
known_tasks = KnownTasks.new("knowntasks")
git_log = NewLog.new(config, known_tasks)