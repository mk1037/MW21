#!/usr/bin/perl

# Copyright (C) 2017-2025 Marek Momot
#
# This file is part of MW21.
#
# MW21 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# MW21 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MW21.  If not, see <http://www.gnu.org/licenses/>.

use File::Copy qw(move);
use File::Find;

die "Usage: $0 input_dir\n" if @ARGV < 1;

my $counter = 0;

$source_dir = "@ARGV[0]";

print "CLEANING NAMES:\n";
print "IN: $source_dir\n";

@finded = find_to_array($source_dir);

my %names;

foreach(@finded) {
   chomp;
   $names{cleanName($_)} = $_;
}

foreach my $sorted_name (sort keys %names) {

    my $new_name = $sorted_name;
    my $old_name = $names{$sorted_name};
    print "-------------------------------\n";
    print "$old_name\n";
    print "$new_name\n";
    move($source_dir ."/" . $old_name, $source_dir ."/" . $new_name);
    $counter++;
   
}

sub cleanName {
    chomp $_[0];
    $old_name = "$_[0]";
    $new_name = "$_[0]";

    $new_name =~ s/Ą/A/g;
    $new_name =~ s/Ć/C/g;
    $new_name =~ s/Ę/E/g;
    $new_name =~ s/Ł/L/g;
    $new_name =~ s/Ń/N/g;
    $new_name =~ s/Ó/O/g;
    $new_name =~ s/Ś/S/g;
    $new_name =~ s/Ź/Z/g;
    $new_name =~ s/Ż/Z/g;

    $new_name =~ s/ą/a/g;
    $new_name =~ s/ć/c/g;
    $new_name =~ s/ę/e/g;
    $new_name =~ s/ł/l/g;
    $new_name =~ s/ń/n/g;
    $new_name =~ s/ó/o/g;
    $new_name =~ s/ś/s/g;
    $new_name =~ s/ź/z/g;
    $new_name =~ s/ż/z/g;

    $new_name =~ s/[^[:ascii:]]//g;
    $new_name =~ s/ /_/g;
    $new_name =~ s/[^A-Za-z0-9_.]//g;

    return $new_name;
}

sub find_to_array {
    my @array;
    find( sub { -f && push @array, $_ }, "$_[0]" );
    return @array;
}

