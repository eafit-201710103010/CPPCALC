require 'ast'
require 'scanner'
require 'token'
require 'calcex'
#dasd
class Parser
  def initialize istream
    @scan = Scanner.new istream
  end

  def parse
    return prog
  end

  def prog
    result = expr
    t = @scan.getToken

    case t.type
    when :eof
      print "Expected EOF. Found ", t.type, ".\n"
      raise ParseError.new
    end

    result
  end

  def expr
    restExpr term
  end

  def restExpr e 
    t = @scan.getToken

    case t.type
    when :add
      return restExpr(AddNode.new(e, term))
    when :sub
      return restExpr(SubNode.new(e, term))
    else
      @scan.putBackToken
    end

    e
  end

  def term
    restTerm storable
    
  end

  def restTerm e
    t = @scan.getToken

    case t.type
    when :times
      return restTerm(TimesNode.new(e, storable))
    when :divide
      return restTerm(DivideNode.new(e, storable))
    else
      @scan.putBackToken

    end
    e
  end

  def storable
    result  = factor
    t = @scan.getToken
    case t.type
    when :keyword
      unless t.lex == "s"
        print "Expected S found ", t.lex
        raise ParserError.new
      end
    else
      @scan.putBackToken
    end
    result
  end

  def factor
    t = @scan.getToken
    case t.type
    when :number
      return NumNode.new t.lex.to_i
    when :keyword
      unless t.lex == "R"
        print "Expected R found", t.lex
        raise ParseError.new
      end
      return RecallNode.new
    when :lparen
      result = expr
      t = @scan.getToken
      unless t.type  == :rparen
        print "Expected )"
        raise ParseError.new
      end
      return result
    else
      print "Expected numbre, R, ("
      raise ParseError.new
    end
  end
  
  private :prog, :expr, :restExpr, :term, :restTerm, :storable, :factor
end
