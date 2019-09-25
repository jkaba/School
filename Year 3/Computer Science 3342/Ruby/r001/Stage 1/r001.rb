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

  def initialize(config, entry_string, known_tasks)
    config.putsq entry_string
  end
end

class GitLog
  def initialize(config, git_log_source, known_tasks = nil)
    if git_log_source.class == Array then
      @git_log = git_log_source
      return
    end
    @git_log = Array.new
    git_log_source.each_line do | line |
      catch :skip_entry do
        @git_log.push(LogEntry.new(config, line, known_tasks))
      end
    end
  end
  def include?(entry)
    @git_log.include?(entry)
  end
end

class NewLog
  def initialize(config, known_tasks)
    if config.git_from_file then
      stdout = IO.read("windowsCurrentLog")
    else
      stdout = `git log`
    end
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

