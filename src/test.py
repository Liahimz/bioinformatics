file = str(input())

with open('/home/michael/Desktop/bioinformatics/build/' + file, 'r') as f:
	lines = f.readlines()
	M_input = int(lines[0].strip())
	N_input = int(lines[1].strip())
	Spectrum = list(lines[2].strip().split(' '))
	Spectrum_input = [int(x) for x in Spectrum]

masses = []
with open('/home/michael/Desktop/bioinformatics/build/masses.txt', 'r') as f:
	lines = f.readlines()
	for line in lines:
		masses.append(list(line.strip().split(' ')))

masses_nums = [int(x[1]) for x in masses]
unique_nums = []
for x in masses_nums:
	if x not in unique_nums:
		unique_nums.append(x)

def Expand(peptides):
	new_res = []
	for peptide in peptides:
		for num in unique_nums:
			curr = peptide.copy()
			curr.append(num)
			new_res.append(curr)
	return new_res

def Mass(peptide):
	return sum(peptide)

def ParentMass(Spectrum):
	return Spectrum[-1]

def Cyclospectrum(peptide):
	res = [0]
	combs = []
	peptide_copy = peptide + peptide
	for i in range(1, len(peptide)):
		for j in range(len(peptide)):
			combs += [peptide_copy[j : j + i]] 	
	for cmb in combs:
		res.append(Mass(cmb))
	res.append(Mass(peptide))
	#print(sorted(res))
	return sorted(res)

def LinearSpectrum(peptide):
	res = [0]
	combs = []
	for i in range(1, len(peptide)):
		for j in range(len(peptide)):
			combs += [peptide[j : j + i]] 	
	for cmb in combs:
		res.append(Mass(cmb))
	res.append(Mass(peptide))
	return sorted(res)

def Score(peptide, Spectrum):
	res = 0
	mult_dict = {}
	for c in Spectrum:
		try:
			mult_dict[c] += 1
		except KeyError:
			mult_dict.update({c : 1})
	check = LinearSpectrum(peptide)
	#print(check)
	p_mult_dict = {}
	for c in check:
		try:
			p_mult_dict[c] +=1
		except:
			p_mult_dict.update({c : 1})
	for key in p_mult_dict:
		try:
			if p_mult_dict[key] >= mult_dict[key]:
				res += mult_dict[key]
			elif p_mult_dict[key] < mult_dict[key]:
				res += p_mult_dict[key]
		except KeyError:
			res += 0
	return res

def CycloScore(peptide, Spectrum):
	res = 0
	mult_dict = {}
	for c in Spectrum:
		try:
			mult_dict[c] += 1
		except KeyError:
			mult_dict.update({c : 1})
	check = Cyclospectrum(peptide)
	p_mult_dict = {}
	for c in check:
		try:
			p_mult_dict[c] +=1
		except:
			p_mult_dict.update({c : 1})
	for key in p_mult_dict:
		try:
			if p_mult_dict[key] >= mult_dict[key]:
				res += mult_dict[key]
			elif p_mult_dict[key] < mult_dict[key]:
				res += p_mult_dict[key]
		except KeyError:
			res += 0
	return res

def Cut(leaderboard, Spectrum, N):
	scores = []
	ldr = leaderboard.copy()
	for ppt in ldr:
		scores.append(CycloScore(ppt, Spectrum))
	ldr_ = sorted(ldr, key = lambda x: CycloScore(x, Spectrum), reverse = True)
	scores_ = sorted(scores, reverse = True)
	for i in range(N, len(ldr_)):
		if scores_[i] < scores_[N-1]:
			return ldr_[:i]
	return ldr_

def convolution(Spectrum, M):
	res = []
	for mass1 in Spectrum:
		for mass2 in Spectrum:
			curr_diff = mass1 - mass2
			if curr_diff > 0:
				res.append(curr_diff)
	keys = set(res)
	res_f = {}
	for key in keys:
		if key >= 57 and key <= 200:
			count = 0
			for r in res:
				if r == key:
					count += 1 
			res_f.update({key: count})
	res_f = sorted(res_f.items(), key = lambda x: x[1], reverse=True)
	res_f = dict(res_f)
	scores = [res_f[key] for key in res_f]
	keys = [key for key in res_f]
	for i in range(M, len(keys)):
		if scores[i] < scores[M-1]:
			return keys[:i]
	return keys


def ConvolutionCyclopetideSequencing(Spectrum, N, M):
	global unique_nums
	leaderboard = [[]]
	leader_peptide = []
	bad_ppt = []
	bestScore = 0
	conv = convolution(Spectrum, M)
	unique_nums = conv

	best = []
	while len(leaderboard) > 0:
		bad_ppt = []
		leaderboard = Expand(leaderboard)
		for ppt in leaderboard:
			if Mass(ppt) == max(Spectrum):
				currentScore = CycloScore(ppt, Spectrum)
				if currentScore > bestScore:
					leader_peptide = ppt 
					bestScore = currentScore
					print('^')
					print(leader_peptide)
					print('^')
					best.append((ppt, currentScore))
			elif Mass(ppt) > max(Spectrum):
				bad_ppt.append(ppt)
		for ppt in bad_ppt:
			leaderboard.remove(ppt)
		leaderboard = Cut(leaderboard, Spectrum, N)

	print(best)
	return leader_peptide


res = ConvolutionCyclopetideSequencing(Spectrum_input, N_input, M_input)

with open('/home/michael/Desktop/bioinformatics/build/task20_output.txt', 'w') as f:
	for i in range(len(res)):
		f.write(str(res[i]))
		if i != len(res) - 1:
			f.write('-')