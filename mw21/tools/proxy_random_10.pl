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

use List::Util 'shuffle';
use File::Copy qw(copy);
use File::Find;

die "Usage: $0 input_dir absolute_output_dir\n" if @ARGV < 2;

$source_dir = "@ARGV[0]";
$dest_dir = "@ARGV[1]";
$offset = "@ARGV[2]";

print "PROXY FILES:\n";
print "FROM: $source_dir\n";
print "TO: $dest_dir\n";

@finded = find_to_array($source_dir);

@shuffled = shuffle(@finded);

for($i = 0; $i < 10; $i++) {
    $src_path = $shuffled[$i];
    $relative_path = $src_path;
    $relative_path =~ s/.+\///g;

    $cleaned_filename = cleanName($relative_path);
    print "------------------------------------------\nLINKING\n";
    print "Absolute path is $src_path\n";
    print "Relative path is $relative_path\n";
    $new_path = $dest_dir . "/" . $cleaned_filename;
    print "$new_path\n";
    symlink($src_path, $new_path);
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
    find( sub { -f && push @array, File::Spec->rel2abs($_) }, "$_[0]" );
    return @array;
}

