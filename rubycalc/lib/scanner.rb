require 'stringio'
require 'calcex'

class Scanner
  def initialize(inStream)
    @istream = inStream
    @keywords = Set.new(["S","R"])
    @lineCount = 1
    @colCount = -1
    @needToken = true
    @lastToken = nil
  end
  
  def putBackToken()
    @needToken = false
  end

  def getToken()
    unless @needToken
      @needToken = true
      return @lastToken
    end
    
    state = 0
    foundOne = false
    c = @istream.getc()
    
    if @istream.eof
      @lastToken = Token.new(:eof,@lineCount,@colCount)
      return @lastToken
    end
    
    until foundOne
      @colCount = @colCount + 1
      case state
      when 0
        lex = ""
        column = @colCount
        line = @lineCount
        if isLetter(c) then state=1
        elsif isDigit(c) then state=2
        elsif c == ?+ then state = 3
        elsif c == ?- then state = 4
        elsif c == ?* then state = 5
        elsif c == ?/ then state = 6
        elsif c == ?( then state = 7
        elsif c == ?) then state = 8
        elsif c == ?\n then 
          @colCount = -1
          @lineCount = @lineCount+1
        elsif isWhiteSpace(c) then state = state #ignore whitespace
        elsif @istream.eof() then
          @foundOne = true
          type = :eof
        else
          puts "Unrecognized Token found at line ",line," and column ",column,"\n"
          raise UnrecognizedTokenException # "Unrecognized Token"
        end
      when 1
        if isLetter(c) or isDigit(c) then state = 1
        else
          if @keywords.include?(lex) then
            foundOne = true
            type = :keyword
          else
            foundOne = true
            type = :identifier
          end
        end
      when 2
        if isDigit(c) then state = 2
        else
          type = :number
          foundOne = true
        end
      when 3
        type = :add
        foundOne = true
      when 4
        type = :sub
        foundOne = true
      when 5
        type = :times
        foundOne = true
      when 6
        type = :divide
        foundOne = true
      when 7
        type = :lparen
        foundOne = true
      when 8
        type = :rparen
        foundOne = true
      end

      if !foundOne then
        lex.concat(c)
        c = @istream.getc()
      end

    end
   
    @istream.ungetc(c)   
    @colCount = @colCount - 1
    if type == :number or type == :identifier or type == :keyword then
      t = LexicalToken.new(type,lex,line,column)
    else
      t = Token.new(type,line,column)
    end

    @lastToken = t
    return t 
  end

  #private
  #private :isLetter, :isDigit, :isWhiteSpace
  def isLetter(c) 
    /[A-Za-z]/ =~ c
    #return ((?a <= c and c <= ?z) or (?A <= c and c <= ?Z))
  end
  
  def isDigit(c)
    /[0-9]/ =~ c
    #return (?0 <= c and c <= ?9)
  end
  
  def isWhiteSpace(c)
    /[ \n\t\v\f]/ =~ c
    #return (c == ?\  or c == ?\n or c == ?\t)
  end
end
