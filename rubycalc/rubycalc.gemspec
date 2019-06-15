
Gem::Specification.new do |s|
  s.name    = 'rubycalc'
  s.version = '0.0.2'
  s.date    = '2017-10-31'
  s.summary = 'Another calculator in ruby'
  s.description = 'An calculator implementation on ruby'
  s.author  = 'Daniel Mesa - Juan Francisco Cardona Mc'
  s.email   = 'damesaa@eafit.edu.co'
  s.homepage = 'http://www1.eafit.edu.co/fcardona/cursos/st0244/rubycal'
  s.files    = ["lib/token.rb",
                "lib/scanner.rb",
                "lib/ast.rb",
                "lib/parser.rb",
                "lib/calculator.rb",
                "lib/calcex.rb"]
  s.license  = 'ARTISTIC'
  s.executables << 'rubycalc'
end
