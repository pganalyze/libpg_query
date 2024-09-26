#!/usr/bin/env ruby

require 'bundler'
require 'json'

class Generator
  def initialize
    @fingerprint_tests = JSON.parse(File.read('./testdata/fingerprint.json'))
  end

  def generate!
    test_lines = []

    @fingerprint_tests.each do |test_def|
      if test_def['disableOnMsvc']
        test_lines << '#ifndef _MSC_VER'
      end

      test_lines << format('  %s,', test_def['input'].inspect)
      test_lines << format('  %s,', test_def['expectedHash'].inspect)

      if test_def['disableOnMsvc']
        test_lines << '#endif'
      end
    end

    File.write './test/fingerprint_tests.c', <<-EOF
const char* tests[] = {
#{test_lines.join("\n")}
};

const size_t testsLength = sizeof(tests)/sizeof(*tests)/2;
EOF
  end
end

Generator.new.generate!
